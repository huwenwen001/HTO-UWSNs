import pandas as pd
import matplotlib.pyplot as plt

energy=pd.read_csv("../raw_results/energy_trace.csv")
lat=pd.read_csv("../raw_results/latency_trace.csv")
thr=pd.read_csv("../raw_results/throughput.csv")
pdr=pd.read_csv("../raw_results/pdr.csv")
off=pd.read_csv("../raw_results/offloading.csv")

# Figure8 Energy
for c in energy.columns[1:]:
    plt.plot(energy["Cycle"],energy[c],label=c)
plt.legend()
plt.savefig("../fig8.png")
plt.clf()

# Figure9 Latency
for c in lat.columns[1:]:
    plt.plot(lat["Cycle"],lat[c],label=c)
plt.legend()
plt.savefig("../fig9.png")
plt.clf()

# Figure10 Throughput
plt.bar(thr["Protocol"],thr["Throughput"])
plt.savefig("../fig10.png")
plt.clf()

# Figure12 PDR
for c in pdr.columns[1:]:
    plt.plot(pdr["Nodes"],pdr[c],label=c)
plt.legend()
plt.savefig("../fig12.png")
plt.clf()

# Figure14 Offloading
plt.bar(off["Protocol"],off["Efficiency"])
plt.savefig("../fig14.png")
plt.clf()