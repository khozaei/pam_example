#include <stdio.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>

int
pam_function(int num_msg, const struct pam_message **msg,
		 struct pam_response **resp, void *appdata_ptr)
{
	char password[10];
	
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
	result = pam_start("pam_example", "amin", &conv, &pam_handle);
	if (result == PAM_SUCCESS)
	{
		//Authenticate user
		result = pam_authenticate(pam_handle, 0);
		if (result == PAM_SUCCESS)
			printf("pam login successful\n");
		else
			printf("bad login info\n");
	}
	return 0;
}
