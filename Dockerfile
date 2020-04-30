FROM debian:buster

ADD ./ /tmp

RUN	apt-get update;\
	apt-get install -y \
	vim\
	clang\
	git\
	make;

CMD bash	
