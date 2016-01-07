#!/usr/bin/perl
#This is a very simple Perl program which can accomplish the simplest web server function.
#《HTTP权威指南》p119

use Socket;
use Carp;
use FileHandle;

#(1) use port 80 by default, unless overridden on command line
$port = (@ARGV ? $ARGV[0] : 80);

#(2) creat local TCP socket and set it to listen for connection
$proto = getprotobyname('tcp');
socket(S, PF_INET, SOCK_STREAM, $proto) || die;
setsockopt(S, SOL_SOCKET, SO_REUSEADDR, pack("l", 1)) || die;
bind(S, sockaddr_in($port, INADDR_ANY)) || die;
listen(S, SOMAXCONN) || die;

#(3) print a startup message
printf("   <<<Type-O-Serve Accepting on Port %d>>>\n\n", $port);

while(1)
{
    #(4) wait for a connection C
    $cport_caddr = accept(C, S);
    ($cport, $caddr) = sockaddr_in($cport_caddr);
    C->autoflush(1);
    
    #(5) print who the connection is from
    $cname = gethostbyaddr($caddr, AF_INET);
    printf("   <<<Request From '%s'>>>\n", $cname);
    
    #(6) read request msg until blank line, and print on screen
    while($line = <C>)
    {
        print $line;
        if($line = ~ /^\r/){ last; }
    }

    #(7) prompt for response message, and input response line, sending response lines to clinet, until solitary "."
#    printf("   <<<Type Response Followed by '.'>>>\n");
    
#    while( $line = <STDIN>)
#    {
#        $line = ~ s/\r//;
#        $line = ~ s/\n//;
#        if ($line = ~ /^\./) { last; }
#        print C $line . "\r\n";
#    }

    #(7) prepare for the universal reponse message, print on screen and sending to client
    $line = "HTTP/1.1 200 OK \r\nConnection: close\r\nContent-type: text/plain\r\n\r\nHello there!\r\n\r\n";
    
    print $line;
    print C $line;
    
    #(8) close the connection to client, waiting the next connection
    close(C);
}
