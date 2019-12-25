/* Wrapper around Httpd which purpose  is to secure the Server with a Basic Authorization.
 * Copyright Alija Bobija, 2019.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file httpd_basic_auth.h
 * @brief Basic Authorization Wrapper around Htppd
 */ 

#include "esp_http_server.h"

#define ESP_ERR_HTTPD_BASIC_AUTH_BASE                  (ESP_ERR_HTTPD_BASE + 200)            /*!< Starting number of HTTPD_BASIC_AUTH error codes */
#define ESP_ERR_HTTPD_BASIC_AUTH_HEADER_NOT_FOUND      (ESP_ERR_HTTPD_BASIC_AUTH_BASE + 1)   /*!< Authorization header has not found in request */
#define ESP_ERR_HTTPD_BASIC_AUTH_FAIL_TO_GET_HEADER    (ESP_ERR_HTTPD_BASIC_AUTH_BASE + 2)   /*!< Fail to read authorization header */
#define ESP_ERR_HTTPD_BASIC_AUTH_HEADER_INVALID        (ESP_ERR_HTTPD_BASIC_AUTH_BASE + 3)   /*!< Invalid format of authorization header */
#define ESP_ERR_HTTPD_BASIC_AUTH_NOT_AUTHORIZED        (ESP_ERR_HTTPD_BASIC_AUTH_BASE + 4)   /*!< Not authorized */

#ifndef HTTPD_401
	#define HTTPD_401 "401 Unauthorized"
#endif

/**
 * @brief Send error code 401 and set "WWW-Authenticate" header
 * @param[in] req The request being responded to
 * 
 * @return
 *  - ESP_OK on success
 */ 
esp_err_t httpd_basic_auth_resp_send_401(httpd_req_t* req);

/**
 * @brief Read authorization token from request and compare with provided username and password
 * @param[in] req The request being responded to
 * @param[in] username Username
 * @param[in] password Password
 * 
 * @return
 *  - ESP_OK user is authorized
 *  - ESP_ERR_NO_MEM no memory
 *  - ESP_ERR_HTTPD_BASIC_AUTH_HEADER_NOT_FOUND authorization header is not provided in request
 *  - ESP_ERR_HTTPD_BASIC_AUTH_FAIL_TO_GET_HEADER fail to read authorization header
 *  - ESP_ERR_HTTPD_BASIC_AUTH_HEADER_INVALID invalid format of authorization header
 *  - ESP_ERR_HTTPD_BASIC_AUTH_NOT_AUTHORIZED not authorized
 */ 
esp_err_t httpd_basic_auth(httpd_req_t* req, const char* username, const char* password);

#ifdef __cplusplus
}
#endif