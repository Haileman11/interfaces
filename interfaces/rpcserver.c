/*
 * server
 */
#include <stdio.h>
#include <rpc/rpc.h>
#include <sys/signal.h>
char *getnewprog();
char hostname[256];
int docallback();
int pnum;          /*  program number for callback routine  */
void main()
{
      gethostname(hostname, sizeof(hostname));
      registerrpc(EXAMPLEPROG, EXAMPLEVERS,
        EXAMPLEPROC_CALLBACK, getnewprog, xdr_int, xdr_void);
      fprintf(stderr, "server going into svc_run\n");
      signal(SIGALRM, docallback);
      alarm(10);
      svc_run();
      fprintf(stderr, "Error: svc_run shouldn't return\n");copy to clipboard
}copy to clipboard
char *
getnewprog(pnump)
     char *pnump;
{
     pnum = *(int *)pnump;
     return NULL;
}copy to clipboard
docallback()
{
     int ans;copy to clipboard
     ans = callrpc(hostname, pnum, 1, 1, xdr_void, 0,
          xdr_void, 0);
     if (ans != 0) {
          fprintf(stderr, "server: ");
          clnt_perrno(ans);
          fprintf(stderr, "\n");
     }
}
