/**
 * @file handlers.h
 * @brief HTTP API handlers (Go: handlers)
 */

#ifndef HANDLERS_H
#define HANDLERS_H

#include "mongoose.h"

#ifdef __cplusplus
extern "C" {
#endif

/* API 处理器 */
void handle_info(struct mg_connection *c, struct mg_http_message *hm);
void handle_execute_at(struct mg_connection *c, struct mg_http_message *hm);
void handle_set_network(struct mg_connection *c, struct mg_http_message *hm);
void handle_switch(struct mg_connection *c, struct mg_http_message *hm);
void handle_airplane_mode(struct mg_connection *c, struct mg_http_message *hm);
void handle_device_control(struct mg_connection *c, struct mg_http_message *hm);
void handle_clear_cache(struct mg_connection *c, struct mg_http_message *hm);
void handle_get_current_band(struct mg_connection *c, struct mg_http_message *hm);

/* 短信 API */
void handle_sms_list(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_send(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_delete(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_webhook_get(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_webhook_save(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_webhook_test(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_sent_list(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_sent_delete(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_config_get(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_config_save(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_fix_get(struct mg_connection *c, struct mg_http_message *hm);
void handle_sms_fix_set(struct mg_connection *c, struct mg_http_message *hm);

/* OTA更新 API */
void handle_update_version(struct mg_connection *c, struct mg_http_message *hm);
void handle_update_upload(struct mg_connection *c, struct mg_http_message *hm);
void handle_update_download(struct mg_connection *c, struct mg_http_message *hm);
void handle_update_extract(struct mg_connection *c, struct mg_http_message *hm);
void handle_update_install(struct mg_connection *c, struct mg_http_message *hm);
void handle_update_check(struct mg_connection *c, struct mg_http_message *hm);

/* 系统时间 API */
void handle_get_system_time(struct mg_connection *c, struct mg_http_message *hm);
void handle_set_system_time(struct mg_connection *c, struct mg_http_message *hm);

#ifdef __cplusplus
}
#endif

#endif /* HANDLERS_H */
