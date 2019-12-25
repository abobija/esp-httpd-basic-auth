#include "httpd_basic_auth.h"
#include "b64.h"

#include "esp_log.h"

static const char *TAG = "httpd_basic_auth";

esp_err_t httpd_basic_auth_resp_send_401(httpd_req_t* req) {
	esp_err_t ret = httpd_resp_set_status(req, HTTPD_401);

	if(ret == ESP_OK) {
		ret = httpd_resp_set_hdr(req, "WWW-Authenticate", "Basic realm=\"User Visible Realm\"");
	}

	return ret;
}

esp_err_t httpd_basic_auth(httpd_req_t* req, const char* username, const char* password) {
	size_t auth_head_len = 1 + httpd_req_get_hdr_value_len(req, "Authorization");
	
	if(auth_head_len <= 1 + 7) {
		return ESP_ERR_HTTPD_BASIC_AUTH_HEADER_NOT_FOUND;
	}

	char* auth_head = malloc(auth_head_len);

	if(auth_head == NULL) {
		return ESP_ERR_NO_MEM;
	}

	if(httpd_req_get_hdr_value_str(req, "Authorization", auth_head, auth_head_len) != ESP_OK) {
		free(auth_head);
		return ESP_ERR_HTTPD_BASIC_AUTH_FAIL_TO_GET_HEADER;
	}

	ESP_LOGD(TAG, "Header: '%s'", auth_head);

	if(strncmp("Basic", auth_head, 5) != 0) {
		free(auth_head);
		return ESP_ERR_HTTPD_BASIC_AUTH_HEADER_INVALID;
	}
	
	unsigned char* decoded = b64_decode((const unsigned char*) (auth_head + 6), auth_head_len - 6 - 1, NULL);
	free(auth_head);

	if(decoded == NULL) {
		return ESP_ERR_HTTPD_BASIC_AUTH_HEADER_INVALID;
	}

	ESP_LOGD(TAG, "Decoded: '%s'", decoded);

	char* colonDelimiter = strchr((const char*) decoded, ':');

	if(colonDelimiter == NULL) {
		free(decoded);
		return ESP_ERR_HTTPD_BASIC_AUTH_HEADER_INVALID;
	}

	size_t head_username_len = colonDelimiter - (const char*) decoded;
	size_t head_password_len = strlen(colonDelimiter + 1);

	if(strlen(username) != head_username_len
		|| strlen(password) != head_password_len
		|| strncmp(username, (const char*) decoded, head_username_len) != 0 
		|| strncmp(password, colonDelimiter + 1, head_password_len) != 0) {
		free(decoded);
		return ESP_ERR_HTTPD_BASIC_AUTH_NOT_AUTHORIZED;
	}

	free(decoded);

	return ESP_OK;
}