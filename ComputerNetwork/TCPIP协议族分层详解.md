# TCP/IP协议族分层详解

## 1、TCP/IP的介绍

> 互联网协议族（Internet Protocol Suite，缩写IPS）是一个网络通信模型，以及一整个网络传输协议家族，
> 为互联网的基础通信架构。它常被通称为TCP/IP协议族（TCP/IP Protocol Suite，或TCP/IP Protocols），
> 简称TCP/IP。
>
> TCP/IP提供点对点的链接机制，将数据应该如何封装、定址、传输、路由以及在目的地如何接收，都加以标
> 准化。它通常将软件通信过程抽象化为四个抽象层，采取协议堆栈的方式，分别实现出不同通信协议。协议套组下的各种协议，依其功能不同，被分别归属到这四个层次结构之中，常被视为是简化的七层OSI模型。

## 2、TCP/IP和ISO/OSI 分层比较

![img](https://img-blog.csdn.net/20170402092437916?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

## 3、TCP/IP分层详解

![img](https://img-blog.csdn.net/20170402093731816?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![各层详细介绍](https://img-blog.csdn.net/20170402095551196?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

> IP是一种网络层协议，提供的是一种不可靠的服务，它只是尽可能快地把分组从源结点送到目的结点，但是、并不提供
> 任何可靠性保证。同时被TCP和UDP使用。TCP和UDP的每组数据都通过端系统和每个中间路、由器中的IP层在互联网中
> 进行传输。
>
> ICMP是IP协议的附属协议。IP层用它来与其他主机或路由器交换错误报文和其他重要信息。
>
> IGMP是Internet组管理协议。它用来把一个UDP数据报多播到多个主机。
>
> TCP是一个传输控制协议，它为两台主机提供了可靠性的数据通信，它所做的工作包括把应用程序交给它的数据进行合适
> 的分块交给下层的网络层，确认接收到的分组，设置发送最后确认分组的超时时钟等
>
> UDP是用户数据报协议，它为应用层提供了简单的服务，它只是把称作数据报的分组从一台主机发送到另外一台主机，并
> 不保证该数据报能到达另外一端。

## 5、封装和分用

封装

![img](https://img-blog.csdn.net/20170402102838806?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

> 从上层往下层传递时，需要加一个首部，而在数据链路层不仅加首部还要加尾部，到物理层再转化为比特流。

分用

![img](https://img-blog.csdn.net/20170402103856306?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

> 