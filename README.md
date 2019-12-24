# esp-httpd-basic-auth
Httpd Server wrapper for Basic Authorization Security, packaged as ESP-IDF component

## How to use

This directory is an ESP-IDF component. Clone it (or add it as submodule) into `components` directory of the project.

Make sure that you have [`b64`](https://github.com/abobija/esp-idf-b64) component cloned as well, because this component depends upone it.

## Example

```c
#include "httpd_basic_auth.h"

static esp_err_t index_handler(httpd_req_t *req) {
	if(httpd_basic_auth(req, "admin", "test") == ESP_OK) {
		httpd_resp_sendstr(req, "Authorized");
	} else {
		httpd_resp_send_401_basic_auth_err(req);
		httpd_resp_sendstr(req, "Not Authorized");
		return ESP_FAIL;
	}

	return ESP_OK;
}

static const httpd_uri_t index_uri = {
	.uri      = "/",
	.method   = HTTP_GET,
	.handler  = index_handler,
	.user_ctx = NULL
};
```
