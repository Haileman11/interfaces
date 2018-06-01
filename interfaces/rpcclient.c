/*
 * client
 */
#include <stdio.h>
#include <rpc/rpc.h>
int callback();
char hostname[256];
void main()
{
      int x, ans, s;
      SVCXPRT *xprt;
      gethostname(hostname, sizeof(hostname));
      s = RPC_ANYSOCK;
      x = gettransient(IPPROTO_UDP, 1, &s);
      fprintf(stderr, "client gets prognum %d\n", x);
      if ((xprt = svcudp_create(s)) == NULL) {
        fprintf(stderr, "rpc_server: svcudp_create\n");
           exit(1);
      }
      /* protocol is 0 - gettransient does registering
       */
      (void)svc_register(xprt, x, 1, callback, 0);
      ans = callrpc(hostname, EXAMPLEPROG, EXAMPLEVERS,
           EXAMPLEPROC_CALLBACK, xdr_int, &x, xdr_void, 0);
      if ((enum clnt_stat) ans != RPC_SUCCESS) {
           fprintf(stderr, "call: ");
           clnt_perrno(ans);
           fprintf(stderr, "\n");
      }
      svc_run();
      fprintf(stderr, "Error: svc_run shouldn't return\n");
}
callback(rqstp, transp)
      register struct svc_req *rqstp;
      register SVCXPRT *transp;
{
      switch (rqstp->rq_proc) {
           case 0:
                if (!svc_sendreply(transp, xdr_void, 0)) {
                     fprintf(stderr, "err: exampleprog\n");
                     return (1);
                }
                return (0);
           case 1:
                if (!svc_getargs(transp, xdr_void, 0)) {
                     svcerr_decode(transp);
                     return (1);
                }
                fprintf(stderr, "client got callback\n");
                if (!svc_sendreply(transp, xdr_void, 0)) {
                     fprintf(stderr, "err: exampleprog");
                     return (1);
                }
      }
}
