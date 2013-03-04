class InteractiveNetConsoleServer:
    """
    The interactive net console server serves console sessions over a given socket
    interface, using asyncore as its intermediate layer.
    """

    import asyncore as __asyncore
    import socket as __socket
    
    class __Server(__asyncore.dispatcher):

        from code import InteractiveConsole as __IC
        import asyncore as __asyncore

        class __Console(__IC, __asyncore.dispatcher_with_send):
            """
            InteractiveNetConsole is an InteractiveConsole implementation running over
            an asyncore socket interface. Usually, it is being launched by 
            InteractiveNetConsoleServer
            """

            from code import InteractiveConsole as __IC
            from cStringIO import StringIO as __StringIO

            def __init__(self, socket, ps1, ps2, intro):
                import sys
                import asyncore
                asyncore.dispatcher_with_send.__init__(self, socket)
                self.__IC.__init__(self)
                self.__socket = socket
                self.__buffer = self.__StringIO()
                if ps1 == None: ps1 = getattr(sys, 'ps1', '>>> ')
                if ps2 == None: ps2 = getattr(sys, 'ps2', '... ')
                self.ps1 = ps1
                self.ps2 = ps2
                if intro == None: intro = 'InteractiveNetConsole'
                self.write("%s for Python %s on %s\n" % 
                           (intro, sys.version, sys.platform))
                self.write(self.ps1)

            def push(self, line):
                more = self.__IC.push(self, line)
                if more:
                    self.write(self.ps2)
                else:
                    self.write(self.ps1)

            def runcode(self, code):
                import sys
                string_io = self.__StringIO()
                sys.stdout = string_io
                sys.stderr = string_io
                try:
                    self.__IC.runcode(self, code)
                except SystemExit, ex:
                    # This exception is handled transparently
                    self.__socket.close()
                finally:
                    sys.stdout = sys.__stdout__
                    sys.stderr = sys.__stderr__
                    self.__stream(string_io)

            def write(self, text):
                self.__socket.send(text)

            def __stream(self, string_io):
                self.write(string_io.getvalue())

            def handle_read(self):
                data = self.recv(1)
                if data == '\n':
                    self.push(self.__buffer.getvalue())
                    self.__buffer = self.__StringIO()
                else:
                    self.__buffer.write(data)



        def __init__(self, address,
                     ps1, ps2, intro, 
                     socket_family, socket_type,
                     max_backlog):

            import asyncore

            self.__ps1 = ps1
            self.__ps2 = ps2
            self.__intro = intro
            asyncore.dispatcher.__init__(self)
            self.create_socket(socket_family, socket_type)
            self.set_reuse_addr()
            self.bind(address)
            self.listen(max_backlog)
            
        def handle_accept(self):
            pair = self.accept()
            if pair is not None:
                sock, addr = pair
                handler = self.__Console(sock, self.__ps1, self.__ps2, self.__intro)

    # This is the main entry point

    def __init__(self, address, 
                 ps1=None, ps2=None, intro=None, 
                 socket_family=__socket.AF_INET, socket_type=__socket.SOCK_STREAM,
                 max_backlog=5):
        self.server = InteractiveNetConsoleServer.__Server(address, ps1, ps2, intro, 
                               socket_family, socket_type, max_backlog)
        
