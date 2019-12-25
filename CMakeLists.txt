idf_component_register(
    SRCS "httpd_basic_auth.c" "cb64/b64.c"
    INCLUDE_DIRS "." "cb64"
    PRIV_REQUIRES esp_http_server
)