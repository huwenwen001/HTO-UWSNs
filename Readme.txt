# HTO-UWSN-Reproducibility

Reproducibility package for the manuscript:

**Hierarchical Task Offloading for Underwater Wireless Sensor Networks (HTO-UWSN) for Real-Time Aquatic Sports Monitoring**

This repository contains:

- Full NS-3 simulation implementation
- Configuration files
- Raw simulation outputs
- Processed results
- Source data for all figures/tables
- Plot generation scripts
- Reproducibility instructions

---

# Repository Structure

```text
HTO-UWSN-Reproducibility/
│
├── README.md
├── LICENSE
├── .gitignore
│
├── code/
│   └── hto-uwsn.cc
│
├── configs/
│   └── simulation-config.txt
│
├── raw_results/
│   ├── energy_trace.csv
│   ├── latency_trace.csv
│   ├── throughput.csv
│   ├── pdr.csv
│   └── offloading.csv
│
├── processed_results/
│   └── summary_metrics.csv
│
├── figure_source_data/
│   ├── fig8.csv
│   ├── fig9.csv
│   ├── fig10.csv
│   ├── fig11.csv
│   ├── fig12.csv
│   ├── fig13.csv
│   └── fig14.csv
│
└── scripts/
    └── plot_results.py
```

---

# Software Environment

Simulation tested with:

- NS-3 version: 3.38
- OS: Ubuntu 22.04 LTS
- Compiler: g++ 11+
- Python: 3.10+
- Required Python packages:

```bash
pip install matplotlib pandas numpy
```

---

# Dependencies

Required NS-3 modules:

- core
- network
- mobility
- internet
- energy

---

# Simulation Parameters

| Parameter | Value |
|---|---|
| Number of Sensor Nodes | 100 |
| Simulation Area | 100 × 100 m |
| Deployment Depth | 1–15 m |
| Communication Range | 50 m |
| Acoustic Data Rate | 10 kbps per node |
| Sound Speed | 1500 m/s |
| Spreading Factor | 1.5 |
| MAC Protocol | TDMA |
| Routing | Hierarchical Clustering |
| Simulation Duration | 24 hours |

Note:

Reported throughput in manuscript is **aggregate network throughput** at the sink/base station generated from multiple concurrent clustered transmissions, not per-node acoustic link rate.

---

# Build NS-3

Clone NS-3:

```bash
git clone https://gitlab.com/nsnam/ns-3-dev.git
cd ns-3-dev
./ns3 configure
./ns3 build
```

---

# Install Simulation Code

Copy:

```text
code/hto-uwsn.cc
```

into:

```text
ns-3-dev/scratch/
```

---

# Run Simulation

Execute:

```bash
./ns3 run scratch/hto-uwsn
```

Simulation produces:

```text
raw_results/
  energy_trace.csv
  latency_trace.csv
  throughput.csv
  pdr.csv
  offloading.csv
```

---

# Reproduce Figures

Go to scripts directory:

```bash
cd scripts
python3 plot_results.py
```

Generated manuscript figures:

- fig8.png Energy Consumption
- fig9.png Latency
- fig10.png Throughput
- fig11.png Resource Utilization
- fig12.png Packet Delivery
- fig13.png Athlete Monitoring Metrics
- fig14.png Task Offloading Efficiency

---

# Mapping Figures to Source Data

| Manuscript Figure | Source File |
|---|---|
| Figure 8 | figure_source_data/fig8.csv |
| Figure 9 | figure_source_data/fig9.csv |
| Figure 10 | figure_source_data/fig10.csv |
| Figure 11 | figure_source_data/fig11.csv |
| Figure 12 | figure_source_data/fig12.csv |
| Figure 13 | figure_source_data/fig13.csv |
| Figure 14 | figure_source_data/fig14.csv |

All manuscript figures and numerical results can be traced to CSV data in this repository.

---

# Output Metrics Generated

Simulation generates:

- Energy consumption
- End-to-end latency
- Throughput
- Packet delivery ratio
- Resource utilization
- Task offloading efficiency
- Motion tracking accuracy
- Physiological signal reliability
- Feedback responsiveness

---

# Protocol Comparison Included

Compared protocols:

1. HTO-UWSN
2. RPSC-WIN
3. RTC-CSF
4. EE-MCBR

All protocols use identical simulation settings for fair comparison.

---

# Reproducing Tables

Tables in manuscript are generated from:

```text
processed_results/summary_metrics.csv
```

Each reported value can be regenerated directly from raw traces.

---

# Stable Release

Repository release used in revised manuscript:

```text
v1.0-revised-manuscript
```

Cited commit/tag:

```text
[Insert Git commit hash after final push]
```

Example:

```text
Commit: 7f3c2d9
```

---

# Code Availability

All custom simulation code, mathematical implementation, plotting scripts, and result generation scripts are openly available in this repository.

No proprietary software is required beyond NS-3 and standard open-source Python packages.

---

# Notes on Reproducibility

Before submission verify:

- Remove private paths
- Remove temporary files
- Remove broken scripts
- Confirm all figures regenerate
- Confirm every table maps to CSV source data

Checklist:

- [ ] NS-3 simulation builds successfully  
- [ ] Figures regenerate  
- [ ] CSV outputs match manuscript  
- [ ] Release tag created  
- [ ] Commit hash inserted in manuscript  

---

# Citation

If using this repository, please cite the corresponding manuscript.

---

# License

This repository is released under the MIT License.