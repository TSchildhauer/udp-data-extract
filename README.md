# udp-data-extract
Listen to UDP ports and parse data

## Requirements


## Helpful Tools
Listen to TCP ports using python
```
python tools/log_tcp_stream.py -p <port>
```

Send udp commands
```
python tools/test_control_channel.py
```

# Solution

## Task 1
The tcp stream appears to be sending 3 signals:
`out1` is following a sign wave with a magnitude +-5.0 and a frequency of 0.5Hz or a cycle of 2 seconds.
`out2` is following a trinangle wave with the same magnitude and a frequency of 0.25Hz or a cycle of 4 seconds. This signal is producing data only every 200ms, but it is not synced so the exact publish frequency is not confirmed. 
`out3` is publishing a value of either 0.0 or 5.0. The output does not appear to be following a regular pattern.

A visualisation of the data can be seen below:

![Plot of data](./data_plot.png)
