#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_http_server.h"

#define ESP_ERR_HTTPD_BASIC_AUTH_BASE                  (ESP_ERR_HTTPD_BASE + 200)
#define ESP_ERR_HTTPD_BASIC_AUTH_HEADER_NOT_FOUND      (ESP_ERR_HTTPD_BASIC_AUTH_BASE + 1)
#define ESP_ERR_HTTPD_BASIC_AUTH_FAIL_TO_GET_HEADER    (ESP_ERR_HTTPD_BASIC_AUTH_BASE + 2)
#define ESP_ERR_HTTPD_BASIC_AUTH_HEADER_INVALID        (ESP_ERR_HTTPD_BASIC_AUTH_BASE + 3)
#define ESP_ERR_HTTPD_BASIC_AUTH_NOT_AUTHORIZED        (ESP_ERR_HTTPD_BASIC_AUTH_BASE + 3)

#ifndef HTTPD_401
	#define HTTPD_401 "401 Unauthorized"
#endif

esp_err_t httpd_basic_auth_resp_send_401(httpd_req_t* req);
esp_err_t httpd_basic_auth(httpd_req_t* req, const char* username, const char* password);

#ifdef __cplusplus
}
#endif