FROM debian:buster

ADD ./ /tmp

RUN	apt-get update;\
	apt-get install -y\
	vim\
	clang\
	git\
	make\
	ruby\
	valgrind \
	ruby-bundler\
	ruby-dev\
	build-essential\
	valgrind;\
	cd tmp;\
	git clone https://github.com/42Paris/42header.git;\
	mkdir -p ~/.vim/plugin;\
	cp 42header/vim/stdheader.vim ~/.vim/plugin/;\
	git clone https://github.com/42Paris/norminette.git ~/.norminette;\
	cd ~/.norminette/;\
	bundle;\
    echo '\
		set tabstop=4\n\
		syn off\n\
		set colorcolumn=120\n\
		set shiftwidth=4\n\
		set softtabstop=4\n\
		nnoremap m 0i//<Esc>\n\
		nnoremap M 0xx\n\
		vnoremap m dI/*<CR>*/<CR><Esc>kP\n\
		vnoremap M dp2k2dd\n\
	    nnoremap <F2> <C-W>\n\
	    nnoremap <F3> <C-W>n\n\
		nnoremap <F4> <C-W>v\n\
		nnoremap <F5> <C-W>h\n\
		nnoremap <F6> <C-W>j\n\
		nnoremap <F7> <C-W>k\n\
		nnoremap <F8> <C-W>l\n\
		set shell=bash' \
	> ~/.vimrc;\
	echo 'alias norminette="~/.norminette/norminette.rb"' >> ~/.bashrc;
#	source ~/.bashrc;
#These isn't 'leaks' on linuxOS	apt-get install -y leaks;

CMD bash
