
#ifndef _HTTP_CLIENT_H
#define _HTTP_CLIENT_H

typedef enum {
	HTTP_CLIENT_STATE_UNDEFINED = 0,
	HTTP_CLIENT_STATE_IDLE,
	HTTP_CLIENT_STATE_CONNECTING,
	HTTP_CLIENT_STATE_DISCONNECTING,
	HTTP_CLIENT_STATE_RECEIVING,
	HTTP_CLIENT_STATE_SENDING
} t_http_client_state;

void http_client_task ( void );
void http_client_init ( void );

#endif /* _HTTP_CLIENT_H */
