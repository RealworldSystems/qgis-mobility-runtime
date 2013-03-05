from interactivenetconsole import InteractiveNetConsoleServer as INCS
from PyQt4.QtCore import QObject, QTimer, QEventLoop, pyqtSlot, SLOT, SIGNAL
from PyQt4.QtCore import qDebug
from PyQt4.QtGui  import QApplication
import asyncore

incs = INCS(('localhost', 7654))

class AsyncoreQtBridge(QObject):
    def __init__(self):
        QObject.__init__(self)
    
    @pyqtSlot()
    def pull(self):
        asyncore.loop(timeout=0.010, count=1)


timer = QTimer()
timer.setInterval(0)

bridge = AsyncoreQtBridge()

QObject.connect(timer, SIGNAL('timeout()'), bridge, SLOT('pull()'))


timer.start()

#eventLoop = QEventLoop()
#eventLoop.exec_()
