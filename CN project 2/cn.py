"""
import http.server
import socketserver
port = 5555
handler = http.server.SimpleHTTPRequestHandler
http = socketserver.TCPServer(("",port),handler)
print("serving at port",port)
http.serve_forever()
"""

"""
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email import encoders
import os.path
email = 'vaibhavvijay2002@gmail.com'
password = '1965vVv@'
send_to_email = 'tushar.jumla@gmail.com'
subject = 'This is the subject'
message = 'This is my message'
file_location = 'C:\\Users\\dell\\Desktop\\vvvvvv.txt'
msg = MIMEMultipart()
msg['From'] = email
msg['To'] = send_to_email
msg['Subject'] = subject
msg.attach(MIMEText(message, 'plain'))
filename = os.path.basename(file_location)
attachment = open(file_location, "rb")
part = MIMEBase('application', 'octet-stream')
part.set_payload(attachment.read())
encoders.encode_base64(part)
part.add_header('Content-Disposition', "attachment; filename= %s" % filename)
msg.attach(part)
server = smtplib.SMTP('smtp.gmail.com', 587)
server.starttls()
server.login(email, password)
text = msg.as_string()
server.sendmail(email, send_to_email, text)
server.quit()
"""

"""
import socket
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
target = input("scan - ")
t_IP = socket.gethostbyname(target)
print("started scan on - ",t_IP)
def port_scan(port):
  try:
    s.connect((t_IP,port))
    return True
  except:
    return False
port = int(input("port no to be scanned - "))
if port_scan(port):
  print('port', port, 'is open')
else:
  print("port", port, "is closed")
"""