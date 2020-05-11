FROM debian:buster

ADD ./ /tmp

RUN	apt-get update;\
	apt-get install -y\
	vim\
	clang\
	git\
	make\
	ruby\
	ruby-bundler\
	ruby-dev\
	build-essential;\
	cd tmp;\
	git clone https://github.com/42Paris/42header.git;\
	mkdir -p ~/.vim/plugin;\
	cp 42header/vim/stdheader.vim ~/.vim/plugin/;\
	git clone https://github.com/42Paris/norminette.git ~/.norminette;\
	cd ~/.norminette/;\
	bundle;\
	echo 'set tabstop=4\nsyn off\nset colorcolumn=120\nset shiftwidth=4\nset softtabstop=4' > ~/.vimrc;\ 
	echo 'alias norminette="~/.norminette/norminette.rb"' >> ~/.bashrc;
#	source ~/.bashrc;
#These isn't 'leaks' on linuxOS	apt-get install -y leaks;

CMD bash
