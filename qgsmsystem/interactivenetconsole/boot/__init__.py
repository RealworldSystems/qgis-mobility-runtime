from interactivenetconsole import InteractiveNetConsoleServer as INCS
from PyQt4.QtCore import qDebug
import asyncore

incs = INCS(('localhost', 6543))
asyncore.loop()
