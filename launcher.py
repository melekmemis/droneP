import subprocess

tx = subprocess.Popen(["python", "Scripts\mavlinkSenderT.py"])
rx = subprocess.Popen(["python", "Scripts\mavlinkRecieverT.py"])

tx.wait()
rx.wait()