TEMPLATE = subdirs

SUBDIRS += Server
SUBDIRS += Client

Client.depends = Server
