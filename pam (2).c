#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <security/_pam_macros.h>

typedef struct {
	char *name, *pw;
} pam_auth_t;

static int auth_pam_talker(int num_msg,
				const struct pam_message ** msg,
				struct pam_response ** resp,
				void *appdata_ptr)
{
	unsigned short i = 0;
	pam_auth_t *userinfo = (pam_auth_t *) appdata_ptr;
	struct pam_response *response = NULL;

	/* parameter sanity checking */
	if (!resp || !msg || !userinfo)
		return PAM_CONV_ERR;

	/* allocate memory to store response */
	response = malloc(num_msg * sizeof(struct pam_response));
	if (!response)
		return PAM_CONV_ERR;

	/* copy values */
	for (i = 0; i < num_msg; ++i) {
		/* initialize to safe values */
		response[i].resp_retcode = 0;
		response[i].resp = NULL;

		/* select response based on requested output style */
		switch (msg[i]->msg_style) {
			case PAM_PROMPT_ECHO_ON:
				/* on memory allocation failure, auth fails */
				response[i].resp = strdup(userinfo->name);
				break;
			case PAM_PROMPT_ECHO_OFF:
				response[i].resp = strdup(userinfo->pw);
				break;
			default:
				_pam_drop_reply(response, i);
				return PAM_CONV_ERR;
		}
	}

	*resp = response;
	return PAM_SUCCESS;
}


bool pam_auth(char service[], char username[], char password[])
{
    pam_handle_t *pamh=NULL;
    int retval;
    
    pam_auth_t userinfo = {NULL, NULL};

    struct pam_conv conv = {
        &auth_pam_talker,
        (void *) &userinfo
    };

    userinfo.name = username;
    userinfo.pw = password;

    retval = pam_start(service, userinfo.name, &conv, &pamh);

    if (retval == PAM_SUCCESS)
        retval = pam_authenticate(pamh, PAM_DISALLOW_NULL_AUTHTOK);

    if (retval == PAM_SUCCESS)
        retval = pam_acct_mgmt(pamh, PAM_DISALLOW_NULL_AUTHTOK);

    if (pam_end(pamh,retval) != PAM_SUCCESS) {    
        pamh = NULL;
        return false;
    }

    return ( retval == PAM_SUCCESS ? true:false );  
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		return 1;
	}

	return (pam_auth(argv[1], argv[2], argv[3])? 0 : 1);
}
