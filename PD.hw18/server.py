from http.server import HTTPServer, SimpleHTTPRequestHandler
PORT = 8000 
server_address = ('',PORT) 
httpd = HTTPServer(server_address, SimpleHTTPRequestHandler)
print("serving at port %d" %PORT) 
httpd.serve_forever()
