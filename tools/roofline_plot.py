import sys
import matplotlib.pyplot as plt

ai = None
perf = None
if len(sys.argv) == 3:
    memory_bandwidth = float(sys.argv[1])
    system_peak = float(sys.argv[2])
elif len(sys.argv) == 5:
    memory_bandwidth = float(sys.argv[1])
    system_peak = float(sys.argv[2])
    ai = float(sys.argv[3])
    perf = float(sys.argv[4])
else:
    print("Usage: python roofline_plot.py bw peak [ai] [perf]")
    print("       bw:    System bandwidth (GB/s")
    print("       peak:  System peak (GFLOP/s")
    print("       ai:    arithmetic intensity of application (FLOPS/byte)")
    print("       perf:  application performance (GFLOP/s)")
    raise SystemExit()

system_balance = system_peak / memory_bandwidth

if ai:
    xlim = max(50, ai + 10)
else:
    xlim = 50

# plot roofline
plt.plot([0.1, system_balance], [0.1, system_peak], 'b-', linewidth=2)
plt.plot([system_balance, xlim], [system_peak, system_peak], 'b-', linewidth=2)
plt.plot([system_balance, system_balance], [0, system_peak], 'k--')
plt.text(system_balance, 0.1, '{:4.1f}'.format(system_balance))
plt.text(system_balance / 4, system_peak / 4, '{:5.2f} GB/s'.format(memory_bandwidth), rotation=45)
plt.text((xlim - system_balance) / 2, system_peak + 10, '{:5.2f} GFLOP/s'.format(system_peak))

if ai and perf:
    plt.plot(ai, perf, 'o', markersize=10)

plt.ylabel('GFLOP/s')
plt.xlabel('Arithmetic intensity flop/B')
plt.yscale('log')
plt.xscale('log')

plt.show()
