# esp-httpd-basic-auth
Wrapper around Httpd which purpose is to secure the Server with a Basic Authorization, packaged as ESP-IDF component

## How to use

This directory is an ESP-IDF component. Clone it (or add it as submodule) into `components` directory of the project.

Don't forget to provide `--recursive` flag in time of cloning.

```
git clone --recursive https://github.com/abobija/esp-httpd-basic-auth.git httpd_basic_auth
```

## Example

This example will protect uri `/` with username `admin` and password `test`.

```c
#include "httpd_basic_auth.h"

static esp_err_t index_handler(httpd_req_t *req) {
	if(httpd_basic_auth(req, "admin", "test") == ESP_OK) {
		httpd_resp_sendstr(req, "Authorized");
	} else {
		httpd_basic_auth_resp_send_401(req);
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
