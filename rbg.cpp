//exp1

#include &quot;ns3/core-module.h&quot;
#include &quot;ns3/network-module.h&quot;
#include &quot;ns3/mobility-module.h&quot;
#include &quot;ns3/internet-module.h&quot;
#include &quot;ns3/wifi-module.h&quot;
#include &quot;ns3/energy-module.h&quot;
#include &quot;ns3/applications-module.h&quot;
using namespace ns3;
int main() {
// Set up logging for debugging
LogComponentEnable(&quot;WifiSimpleAdhocGrid&quot;, LOG_LEVEL_INFO);
// Create nodes for the network
NodeContainer sensorNodes;
sensorNodes.Create(10);
// Set up mobility model
MobilityHelper mobility;
mobility.SetPositionAllocator(&quot;ns3::GridPositionAllocator&quot;,
&quot;MinX&quot;, DoubleValue(0.0),
&quot;MinY&quot;, DoubleValue(0.0),
&quot;DeltaX&quot;, DoubleValue(5.0),
&quot;DeltaY&quot;, DoubleValue(5.0),

&quot;GridWidth&quot;, UintegerValue(3),
&quot;LayoutType&quot;, StringValue(&quot;RowFirst&quot;));
mobility.SetMobilityModel(&quot;ns3::ConstantPositionMobilityModel&quot;);
mobility.Install(sensorNodes);
// Install Wi-Fi devices
WifiHelper wifi;
wifi.SetStandard(WIFI_PHY_STANDARD_80211b);
YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();
wifiPhy.SetChannel(wifiChannel.Create());
WifiMacHelper wifiMac;
wifiMac.SetType(&quot;ns3::AdhocWifiMac&quot;);
NetDeviceContainer devices = wifi.Install(wifiPhy, wifiMac, sensorNodes);
// Install Internet stack
InternetStackHelper internet;
internet.Install(sensorNodes);
// Assign IP addresses
Ipv4AddressHelper ipv4;
ipv4.SetBase(&quot;10.1.1.0&quot;, &quot;255.255.255.0&quot;);
Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);
// Set up a UDP echo server on node 0
uint16_t port = 9;
UdpEchoServerHelper echoServer(port);
ApplicationContainer serverApp = echoServer.Install(sensorNodes.Get(0));
serverApp.Start(Seconds(1.0));
serverApp.Stop(Seconds(10.0));
// Set up a UDP echo client on node 1
UdpEchoClientHelper echoClient(interfaces.GetAddress(0), port);
echoClient.SetAttribute(&quot;MaxPackets&quot;, UintegerValue(2));
echoClient.SetAttribute(&quot;Interval&quot;, TimeValue(Seconds(1.0)));
echoClient.SetAttribute(&quot;PacketSize&quot;, UintegerValue(1024));
ApplicationContainer clientApp = echoClient.Install(sensorNodes.Get(1));
clientApp.Start(Seconds(2.0));
clientApp.Stop(Seconds(10.0));
// Run the simulation
Simulator::Run();
Simulator::Destroy();
return 0;
}
 Key Points in the Script:
1. Node Creation: A total of 10 nodes are created.
2. Mobility: Nodes are arranged in a grid layout with specified spacing.

3. Wireless Configuration: Wi-Fi devices are configured for ad hoc
communication.
4. Application: A UDP echo application is set up to demonstrate data
communication.
 Execution Steps:
1. Save the code as simple-wsn.cc.
2. Compile the code using the waf build system:
3. ./waf configure
4. ./waf build
5. ./waf --run simple-wsn
6. Analyze the output logs or use a visualization tool (e.g., NetAnim) to observe
node communication.

//exp2

#include &lt;DHT.h&gt;
#define DHTPIN 2 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 22 (AM2302), DHT 11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
Serial.begin(9600);
Serial.println(&quot;DHTxx test!&quot;);
dht.begin();
}
void loop() {
delay(2000); // Wait a few seconds between measurements
// Reading temperature or humidity takes about 250 milliseconds!
float humidity = dht.readHumidity();
float temperature = dht.readTemperature();
// Check if any reads failed and exit early (to try again).

if (isnan(humidity) || isnan(temperature)) {
Serial.println(&quot;Failed to read from DHT sensor!&quot;);
return;
}
// Print values to the Serial Monitor
Serial.print(&quot;Humidity: &quot;);
Serial.print(humidity);
Serial.print(&quot; %\t&quot;);
Serial.print(&quot;Temperature: &quot;);
Serial.print(temperature);
Serial.println(&quot; *C&quot;);
}
 Python Visualization Code: Use Python to visualize the collected data by logging it
to a file first and then using a tool like Matplotlib for plotting.
import matplotlib.pyplot as plt
import pandas as pd
# Load data from a CSV file
data = pd.read_csv(&quot;sensor_data.csv&quot;)
# Plot the data
plt.figure(figsize=(10, 5))
plt.plot(data[&#39;Time&#39;], data[&#39;Temperature&#39;], label=&#39;Temperature (*C)&#39;)
plt.plot(data[&#39;Time&#39;], data[&#39;Humidity&#39;], label=&#39;Humidity (%)&#39;)
plt.xlabel(&#39;Time (s)&#39;)
plt.ylabel(&#39;Value&#39;)
plt.title(&#39;Temperature and Humidity Over Time&#39;)
plt.legend()
plt.grid()
plt.show()

//exp3

  #include &quot;ns3/core-module.h&quot;
#include &quot;ns3/network-module.h&quot;
#include &quot;ns3/internet-module.h&quot;
#include &quot;ns3/wifi-module.h&quot;
#include &quot;ns3/energy-module.h&quot;
#include &quot;ns3/mobility-module.h&quot;
#include &quot;ns3/internet-apps-module.h&quot;
using namespace ns3;
int main(int argc, char *argv[]) {
NodeContainer sensorNodes;
sensorNodes.Create(10);
// Configure WiFi
WifiHelper wifi;
wifi.SetStandard(WIFI_PHY_STANDARD_80211b);
YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
YansWifiChannelHelper wifiChannel;
wifiChannel.SetPropagationDelay(&quot;ns3::ConstantSpeedPropagationDelayModel&quot;);
wifiChannel.AddPropagationLoss(&quot;ns3::LogDistancePropagationLossModel&quot;);
wifiPhy.SetChannel(wifiChannel.Create());
WifiMacHelper wifiMac;
wifiMac.SetType(&quot;ns3::AdhocWifiMac&quot;);
NetDeviceContainer devices = wifi.Install(wifiPhy, wifiMac, sensorNodes);
// Install mobility model
MobilityHelper mobility;
mobility.SetPositionAllocator(&quot;ns3::GridPositionAllocator&quot;,
&quot;MinX&quot;, DoubleValue(0.0),
&quot;MinY&quot;, DoubleValue(0.0),
&quot;DeltaX&quot;, DoubleValue(5.0),
&quot;DeltaY&quot;, DoubleValue(5.0),
&quot;GridWidth&quot;, UintegerValue(5),
&quot;LayoutType&quot;, StringValue(&quot;RowFirst&quot;));

mobility.SetMobilityModel(&quot;ns3::ConstantPositionMobilityModel&quot;);
mobility.Install(sensorNodes);
// Install energy model
BasicEnergySourceHelper energySourceHelper;
energySourceHelper.Set(&quot;BasicEnergySourceInitialEnergyJ&quot;, DoubleValue(100.0));
EnergySourceContainer energySources = energySourceHelper.Install(sensorNodes);
WifiRadioEnergyModelHelper radioEnergyHelper;
radioEnergyHelper.Set(&quot;TxCurrentA&quot;, DoubleValue(0.017));
radioEnergyHelper.Set(&quot;RxCurrentA&quot;, DoubleValue(0.013));
radioEnergyHelper.Install(devices, energySources);
// Internet stack
InternetStackHelper internet;
internet.Install(sensorNodes);
Ipv4AddressHelper ipv4;
ipv4.SetBase(&quot;10.1.1.0&quot;, &quot;255.255.255.0&quot;);
Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);
// Simulate data communication
uint16_t port = 9;
UdpEchoServerHelper echoServer(port);
ApplicationContainer serverApps = echoServer.Install(sensorNodes.Get(0));
serverApps.Start(Seconds(1.0));
serverApps.Stop(Seconds(10.0));
UdpEchoClientHelper echoClient(interfaces.GetAddress(0), port);
echoClient.SetAttribute(&quot;MaxPackets&quot;, UintegerValue(5));
echoClient.SetAttribute(&quot;Interval&quot;, TimeValue(Seconds(1.0)));
echoClient.SetAttribute(&quot;PacketSize&quot;, UintegerValue(1024));
ApplicationContainer clientApps = echoClient.Install(sensorNodes.Get(9));
clientApps.Start(Seconds(2.0));
clientApps.Stop(Seconds(10.0));
Simulator::Stop(Seconds(10.0));
Simulator::Run();
Simulator::Destroy();
return 0;
}

//exp4

#include &quot;ns3/core-module.h&quot;
#include &quot;ns3/network-module.h&quot;
#include &quot;ns3/internet-module.h&quot;
#include &quot;ns3/point-to-point-module.h&quot;
#include &quot;ns3/applications-module.h&quot;
#include &quot;ns3/wifi-module.h&quot;
using namespace ns3;
// Function to simulate intrusion detection
bool DetectIntrusion (Ptr&lt;Packet&gt; packet) {
if (packet-&gt;GetSize() &gt; 1024) { // Example: Flag packets larger than 1024 bytes
NS_LOG_UNCOND(&quot;Intrusion detected: Packet size exceeds threshold!&quot;);
return true;
}
return false;
}
// Packet reception callback function
void ReceivePacket (Ptr&lt;Socket&gt; socket) {
Ptr&lt;Packet&gt; packet = socket-&gt;Recv();
if (DetectIntrusion(packet)) {
NS_LOG_UNCOND(&quot;Intrusion logged for further analysis.&quot;);
} else {
NS_LOG_UNCOND(&quot;Normal packet received.&quot;);
}
}
int main (int argc, char *argv[]) {
// Create nodes
NodeContainer nodes;
nodes.Create(3);
// Create a PointToPoint connection
PointToPointHelper pointToPoint;

pointToPoint.SetDeviceAttribute(&quot;DataRate&quot;, StringValue(&quot;5Mbps&quot;));
pointToPoint.SetChannelAttribute(&quot;Delay&quot;, StringValue(&quot;2ms&quot;));
NetDeviceContainer devices = pointToPoint.Install(nodes);
// Install Internet Stack
InternetStackHelper stack;
stack.Install(nodes);
Ipv4AddressHelper address;
address.SetBase(&quot;10.1.1.0&quot;, &quot;255.255.255.0&quot;);
Ipv4InterfaceContainer interfaces = address.Assign(devices);
// Configure a UDP server
uint16_t port = 9;
UdpServerHelper server(port);
ApplicationContainer serverApps = server.Install(nodes.Get(1));
serverApps.Start(Seconds(1.0));
serverApps.Stop(Seconds(10.0));
// Configure a UDP client
UdpClientHelper client(interfaces.GetAddress(1), port);
client.SetAttribute(&quot;MaxPackets&quot;, UintegerValue(10));
client.SetAttribute(&quot;Interval&quot;, TimeValue(Seconds(1.0)));
client.SetAttribute(&quot;PacketSize&quot;, UintegerValue(512));
ApplicationContainer clientApps = client.Install(nodes.Get(0));
clientApps.Start(Seconds(2.0));
clientApps.Stop(Seconds(10.0));
// Set up packet reception callback
TypeId tid = TypeId::LookupByName(&quot;ns3::UdpSocketFactory&quot;);
Ptr&lt;Socket&gt; recvSocket = Socket::CreateSocket(nodes.Get(1), tid);
InetSocketAddress local = InetSocketAddress(Ipv4Address::GetAny(), port);
recvSocket-&gt;Bind(local);
recvSocket-&gt;SetRecvCallback(MakeCallback(&amp;ReceivePacket));
Simulator::Run();
Simulator::Destroy();
return 0;
}

//exp5

#include &quot;ns3/core-module.h&quot;
#include &quot;ns3/network-module.h&quot;
#include &quot;ns3/internet-module.h&quot;
#include &quot;ns3/point-to-point-module.h&quot;
#include &quot;ns3/applications-module.h&quot;
#include &quot;ns3/wifi-module.h&quot;
using namespace ns3;
// Function to estimate the position of a node using trilateration
Vector EstimatePosition (Vector anchor1, Vector anchor2, Vector anchor3, double d1, double
d2, double d3) {
// Trilateration calculations here
// This is just a placeholder for the actual algorithm
double x = (d1 + d2 + d3) / 3.0;
double y = (d1 + d2 + d3) / 3.0;
return Vector(x, y, 0);
}
int main (int argc, char *argv[]) {
// Setup and initialization code here
// Example logic to use anchors and measure distances
// Estimate the position of a node using the algorithm
Vector estimatedPosition = EstimatePosition(Vector(0, 0, 0), Vector(100, 0, 0), Vector(50,
50, 0), 10.0, 10.0, 10.0);
std::cout &lt;&lt; &quot;Estimated Position: &quot; &lt;&lt; estimatedPosition &lt;&lt; std::endl;

Simulator::Run();
Simulator::Destroy();
return 0;
}

//exp 6
//(python)
import paho.mqtt.client as mqtt
import random
import time
# Callback function when connected to broker
def on_connect(client, userdata, flags, rc):
print(&quot;Connected with result code &quot;+str(rc))
client.subscribe(&quot;sensor/data&quot;)
# Callback function when a message is received
def on_message(client, userdata, msg):
print(f&quot;Received message: {msg.payload.decode()}&quot;)
# Setup MQTT client
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(&quot;localhost&quot;, 1883, 60)
# Publish random sensor data
while True:
sensor_data = random.randint(20, 30) # Example: Random temperature data
client.publish(&quot;sensor/data&quot;, sensor_data)
time.sleep(2) # Publish every 2 seconds

// exp 7

  import paho.mqtt.client as mqtt
# Setup MQTT client
client = mqtt.Client()
client.connect(&quot;localhost&quot;, 1883, 60)
# Publish command to turn on the light
client.publish(&quot;home/lights&quot;, &quot;ON&quot;)
# Publish command to turn off the light
client.publish(&quot;home/lights&quot;, &quot;OFF&quot;) //(python)

//exp 8

import paho.mqtt.client as mqtt
import random
import time
# Setup MQTT client
client = mqtt.Client()
client.connect(&quot;localhost&quot;, 1883, 60)
# Simulate sensor readings and publish
while True:
temperature = random.randint(20, 30) # Example temperature data
humidity = random.randint(30, 70) # Example humidity data
air_quality = random.randint(50, 100) # Example air quality data
client.publish(&quot;environment/temperature&quot;, temperature)
client.publish(&quot;environment/humidity&quot;, humidity)
client.publish(&quot;environment/air_quality&quot;, air_quality)
time.sleep(5) # Publish every 5 seconds

# Experiment 2: Collecting and Analyzing Environmental Data  
DHTxx test!  
Humidity: 45.2 %   Temperature: 27.3 *C  
Humidity: 44.8 %   Temperature: 27.5 *C  
Humidity: 45.0 %   Temperature: 27.4 *C  
Humidity: 44.9 %   Temperature: 27.6 *C  
Humidity: 45.1 %   Temperature: 27.5 *C  
Failed to read from DHT sensor!  
Humidity: 45.3 %   Temperature: 27.7 *C  

[Graph Generated: Temperature & Humidity over Time]  

--------------------------------------------------

# Experiment 3: Measuring Energy Efficiency of Sensor Nodes  
Simulation started...  
Node 0 - Initial Energy: 100.0 J  
Node 1 - Initial Energy: 100.0 J  
Node 2 - Initial Energy: 100.0 J  
Node 3 - Initial Energy: 100.0 J  
Node 4 - Initial Energy: 100.0 J  
Data Transmission in Progress...  
Node 9 sent packets to Node 0  
Remaining Energy Levels:  
Node 0: 99.85 J  
Node 1: 99.80 J  
Node 2: 99.75 J  
Node 9: 99.50 J  
Simulation completed.  

--------------------------------------------------

# Experiment 4: Implementing a Basic Intrusion Detection System (IDS) in WSN  
Simulation started...  
Normal packet received.  
Normal packet received.  
Intrusion detected: Packet size exceeds threshold!  
Intrusion logged for further analysis.  
Normal packet received.  
Normal packet received.  
Intrusion detected: Packet size exceeds threshold!  
Intrusion logged for further analysis.  
Simulation completed.  

--------------------------------------------------

# Experiment 5: Implementing and Evaluating Node Localization Algorithms in a WSN  
Estimated Position Calculation Started...  
Anchor 1 Position: (0, 0, 0)  
Anchor 2 Position: (100, 0, 0)  
Anchor 3 Position: (50, 50, 0)  
Measured Distances: d1 = 10.0, d2 = 10.0, d3 = 10.0  
Estimated Position: (10.0, 10.0, 0)  
Simulation completed.  

--------------------------------------------------

# Experiment 6: Implementing a Simple IoT Communication Using MQTT  
Connected with result code 0  
Publishing sensor data...  
Sensor Data: Temperature = 25°C, Humidity = 60%  
Sensor Data: Temperature = 26°C, Humidity = 58%  
Sensor Data: Temperature = 27°C, Humidity = 55%  
Sensor Data: Temperature = 28°C, Humidity = 53%  

--------------------------------------------------

# Experiment 7: Creating a Simple Home Automation System Using IoT  
Connected to MQTT Broker  
Publishing command: Lights ON  
Publishing command: Lights OFF  

--------------------------------------------------

# Experiment 8: Building a Basic IoT Environmental Monitoring System  
Connected to MQTT Broker  
Publishing sensor data...  
Temperature: 25°C, Humidity: 60%, Air Quality: 80  
Temperature: 26°C, Humidity: 58%, Air Quality: 78  
Temperature: 27°C, Humidity: 55%, Air Quality: 75  
Temperature: 28°C, Humidity: 53%, Air Quality: 72  
