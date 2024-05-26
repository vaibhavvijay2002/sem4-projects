import socket,cv2,pickle,struct
import imutils
import fire 

class Stream(object):
	def __init__(self):
		self.BOX = Send() 

class Send(object):

	def video(self):
		ip = input("Enter The Desitnation IP: ")
		video_file = input("Video File Adddress: ")
		vid = cv2.VideoCapture(video_file)
		client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		host_ip = ip
		port = 9999
		client_socket.connect((host_ip,port))
		if client_socket: 
			while (vid.isOpened()):
				try:
					img, frame = vid.read() 
					frame = imutils.resize(frame,width=380)
					a = pickle.dumps(frame)
					message = struct.pack("Q",len(a))+a
					client_socket.sendall(message)
					cv2.imshow(f"TO: {host_ip}",frame)      
					key = cv2.waitKey(1) & 0xFF
					if key == ord("q"):
						client_socket.close()
				except:
					print('Video Finished!')
					break

	def stream(self):
		vid = cv2.VideoCapture(0)
		client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		ip = input("Enter The Desitnation: ")
		host_ip = ip
		port = 9999
		client_socket.connect((host_ip,port))
		if client_socket: 
			while (vid.isOpened()):
				try:
					img, frame = vid.read()
					frame = imutils.resize(frame,width=380)
					a = pickle.dumps(frame)
					message = struct.pack("Q",len(a))+a
					client_socket.sendall(message)
					cv2.imshow(f"TO: {host_ip}",frame)
					key = cv2.waitKey(1) & 0xFF
					if key == ord("q"):
						client_socket.close()
				except:
					print('Video Finished!')
					break
  
fire.Fire(Stream)
