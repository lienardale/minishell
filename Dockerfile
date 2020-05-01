FROM debian:buster

ADD ./ /tmp

RUN	apt-get update;\
	apt-get install -y \
	vim\
	clang\
	git\
	make;
#These isn't 'leaks' on linuxOS	apt-get install -y leaks;

CMD bash
