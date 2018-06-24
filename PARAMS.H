//---------------------------------------------------------------------------
// Szerzõ: Csonka Gábor okl. villamosmérnök, 1998-2009.
// Author: Gábor Csonka M.Sc. EE., 1998-2009.
//---------------------------------------------------------------------------

// Command line parameter utilities

// Dependencies: nulltstr.*


#ifdef __cplusplus
extern "C" {
#endif

// Searches for a parameter in the parameter list. Returns nonzero if found.
int PrmIsDef(int argscount,char **args,char *arg);

// Searches for parameters of a parameter. (For example -p param1 param2)
// Returns the number of parameters. Pointer set to the first parameter.
// Returns 0 if the main parameter not found or if there are no sub-
// parameters.
char **PrmPrms(int argsc,char **args,char *arg,int *count);

#ifdef __cplusplus
}
#endif


