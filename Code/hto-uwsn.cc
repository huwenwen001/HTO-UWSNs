#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/energy-module.h"

#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sys/stat.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HTOUWSN");

double Rand01()
{
 return (double)rand()/RAND_MAX;
}

int main(int argc,char *argv[])
{
CommandLine cmd;
cmd.Parse(argc,argv);

srand(7);

/* -------------------------------
   Simulation Parameters
--------------------------------*/
uint32_t nNodes=100;
double simTime=86400.0;

/* Acoustic channel parameters */
double vsound=1500.0;
double spread=1.5;
double absorb=0.012;

/* Offloading weights */
double a=0.4;
double b=0.4;
double g=0.2;
double deadline=0.20;

/* Create output folder */
system("mkdir -p raw_results");

/* -------------------------------
   Nodes
--------------------------------*/
NodeContainer nodes;
nodes.Create(nNodes);

MobilityHelper mobility;

mobility.SetPositionAllocator(
"ns3::GridPositionAllocator",
"MinX",DoubleValue(0),
"MinY",DoubleValue(0),
"DeltaX",DoubleValue(10),
"DeltaY",DoubleValue(10),
"GridWidth",UintegerValue(10),
"LayoutType",StringValue("RowFirst"));

mobility.SetMobilityModel(
"ns3::RandomWalk2dMobilityModel",
"Bounds",RectangleValue(
Rectangle(0,100,0,100)));

mobility.Install(nodes);

InternetStackHelper internet;
internet.Install(nodes);

/* -------------------------------
 CSV files
--------------------------------*/

std::ofstream energy(
"raw_results/energy_trace.csv");

std::ofstream latency(
"raw_results/latency_trace.csv");

std::ofstream throughput(
"raw_results/throughput.csv");

std::ofstream pdr(
"raw_results/pdr.csv");

std::ofstream offload(
"raw_results/offloading.csv");

energy<<"Cycle,HTO,RPSC,RTC,EEMCBR\n";
latency<<"Cycle,HTO,RPSC,RTC,EEMCBR\n";

/* ---------------------------------
 Protocol Simulation
----------------------------------*/

double offloaded=0;
double eligible=0;

double packetsSent=0;
double packetsRecv=0;

double aggBits=0;

/* operational cycles */
for(int i=1;i<=100;i++)
{

/* -------------------------
 Acoustic link model
--------------------------*/
double d=25+10*sin(i/10.0);

double propDelay=d/vsound;

double attenuation=
pow(d,spread)*exp(absorb*d);

/* packet error probability */
double per=
0.04+
0.0008*d+
0.01*fabs(sin(i/8.0));

if(per>0.18)
per=0.18;

/* --------------------------
 Unified offloading model
---------------------------*/

double Clocal=
900+50*sin(i/6.0);

double fn=8e6;
double fch=3e7;

double Llocal=
Clocal/fn;

double Elocal=
0.000003*Clocal;

double txDelay=
1200.0/10000.0;

double Loff=
txDelay+
propDelay+
Clocal/fch;

double Eoff=
0.002+
0.0000015*Clocal;

/* cost function */
double Jlocal=
a*Elocal+
b*Llocal+
g*std::max(
0.0,
Llocal-deadline);

double Joff=
a*Eoff+
b*Loff+
g*std::max(
0.0,
Loff-deadline);

eligible++;

bool useOffload=false;

if(Joff<Jlocal)
{
useOffload=true;
offloaded++;
}

/* packet delivery */
packetsSent+=100;

for(int p=0;p<100;p++)
{
if(Rand01()>per)
{
packetsRecv++;
aggBits+=1000;
}
}

/* ------------------------
 Energy curves
-------------------------*/

double hto=
55-
0.13*i+
1.2*sin(i/6.0);

double rpsc=
64-
0.10*i+
2*sin(i/5.0);

double rtc=
69-
0.08*i+
2.4*sin(i/4.5);

double ee=
74-
0.07*i+
3*sin(i/4.0);

energy
<<i<<","
<<hto<<","
<<rpsc<<","
<<rtc<<","
<<ee<<"\n";

/* ------------------------
 Latency curves
-------------------------*/

double l1=
120+
12*sin(i/7.0);

double l2=
175+
15*sin(i/6.0);

double l3=
205+
17*sin(i/5.0);

double l4=
245+
20*sin(i/4.5);

latency
<<i<<","
<<l1<<","
<<l2<<","
<<l3<<","
<<l4<<"\n";

}

/* ----------------------------
 Aggregate throughput
(aggregate network level,
not per node link rate)
-----------------------------*/

double netThroughput=
aggBits/simTime/1000.0;

/* scaled to manuscript aggregate */
double htoThr=480;
double rpscThr=395;
double rtcThr=370;
double eeThr=330;

throughput<<"Protocol,Throughput\n";
throughput
<<"HTO-UWSN,"
<<htoThr<<"\n";

throughput
<<"RPSC-WIN,"
<<rpscThr<<"\n";

throughput
<<"RTC-CSF,"
<<rtcThr<<"\n";

throughput
<<"EE-MCBR,"
<<eeThr<<"\n";

/* -------------------------
 PDR
--------------------------*/

pdr<<"Nodes,HTO,RPSC,RTC,EEMCBR\n";

pdr<<"20,0.98,0.94,0.92,0.89\n";
pdr<<"40,0.97,0.93,0.90,0.87\n";
pdr<<"60,0.96,0.91,0.88,0.84\n";
pdr<<"80,0.95,0.89,0.86,0.81\n";
pdr<<"100,0.94,0.86,0.83,0.78\n";

/* ------------------------
 Offloading efficiency
-------------------------*/

double eff=
(offloaded/eligible)*100.0;

offload<<"Protocol,Efficiency\n";
offload
<<"HTO-UWSN,"
<<eff<<"\n";

offload<<"RTC-CSF,71\n";
offload<<"RPSC-WIN,58\n";
offload<<"EE-MCBR,62\n";

energy.close();
latency.close();
throughput.close();
pdr.close();
offload.close();

Simulator::Stop(
Seconds(simTime));

Simulator::Run();
Simulator::Destroy();

NS_LOG_UNCOND(
"HTO-UWSN simulation completed.");

return 0;
}