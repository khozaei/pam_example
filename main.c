#include <stdio.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <string.h>
#include <stdlib.h>

#define USER "amin"
#define PASS "example_password"
#define MAX_LEN 256

int
pam_function(int num_msg, const struct pam_message **msg,
		 struct pam_response **resp, void *appdata_ptr)
{
	const char *user;
	const char *pass;
	struct pam_response *array_resp;

	user = USER;
	pass = PASS;
	array_resp = (struct pam_response *)malloc( num_msg * sizeof(struct pam_response));
	for (int i = 0; i < num_msg; i++){
		array_resp[i].resp_retcode = 0;
		printf("user=%s,%i msg(%s)\n",user, (int)strnlen(user, MAX_LEN),msg[i]->msg);
		if (strncmp("login:", msg[i]->msg, MAX_LEN) == 0){
			array_resp[i].resp = (char *)malloc(strnlen(user,MAX_LEN) + 1);
			snprintf(array_resp[i].resp,MAX_LEN,"%s",user);
		} else if (strncmp("Password: ", msg[i]->msg, MAX_LEN) == 0){
			array_resp[i].resp = malloc(strnlen(pass,MAX_LEN) + 1);
			snprintf(array_resp[i].resp,MAX_LEN,"%s",pass);
		}
	}

	*resp = array_resp;
	//TODO	
	return PAM_SUCCESS;
}

static struct pam_conv conv = {
	pam_function,
	NULL
};

int
main(int argc, char *argv[])
{
	pam_handle_t *pam_handle;
	int result;

	pam_handle = NULL;
	result = pam_start("pam_example", NULL, &conv, &pam_handle);
	if (result == PAM_SUCCESS)
	{
		//Authenticate user
		result = pam_authenticate(pam_handle, 0);
		if (result == PAM_SUCCESS) {
			result = pam_acct_mgmt(pam_handle, 0);
			if (result == PAM_SUCCESS)
				printf("pam login successful\n");

		} else
			printf("bad login info\n");
	}
	pam_end(pam_handle, result);
	return 0;
}
