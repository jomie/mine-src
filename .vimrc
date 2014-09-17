set display=uhex
"let &termencoding=&encoding
set fileencodings=gbk,utf-8,latin1,ucs-bom,cp936
if $VIM_ENCODING == "utf-8"
  set encoding=utf-8
  set termencoding=utf-8
else
  set encoding=gbk
  set termencoding=gbk
endif

set nocompatible  " Use Vim defaults (much better!)
set bs=2		" allow backspacing over everything in insert mode
"set ai			" always set autoindenting on
"set backup		" keep a backup file
set viminfo='20,\"50	" read/write a .viminfo file, don't store more
			" than 50 lines of registers
set history=50		" keep 50 lines of command line history
set ruler		" show the cursor position all the time

" Only do this part when compiled with support for autocommands
if has("autocmd")
  " In text files, always limit the width of text to 78 characters
  autocmd BufRead *.txt set tw=78
  autocmd BufNewFile,BufRead *.log,*.csv,*.txt,*.gz,*.bz2 set tabstop=10
  " When editing a file, always jump to the last cursor position
  autocmd BufReadPost *
  \ if line("'\"") > 0 && line ("'\"") <= line("$") |
  \   exe "normal! g'\"" |
  \ endif
  autocmd FileType python setlocal expandtab
  autocmd FileType make setlocal noexpandtab
  filetype plugin on
endif

if has("cscope")
  nmap ]c :cscope find c <cword><CR>
  nmap ]d :cscope find d <cword><CR>
  nmap ]e :cscope find e <cword><CR>
  nmap ]f :cscope find f <cword><CR>
  nmap ]g :cscope find g <cword><CR>
  nmap ]i :cscope find i <cword><CR>
  nmap ]I :cscope find i %:t<CR>
  nmap ]s :cscope find s <cword><CR>
  nmap ]t :cscope find t <cword><CR>
nmap <A-1> :ACSBfindsym ref <c-r>=expand("<cword>")<cr>
nmap <A-2> :ACSBfindsym def <c-r>=expand("<cword>")<cr>
nmap <A-3> :ACSBfindsym called <c-r>=expand("<cword>")<cr>
nmap <A-4> :ACSBfindsym caller <c-r>=expand("<cword>")<cr>
nmap <A-5> :ACSBfindsym txt <c-r>=expand("<cword>")<cr>
nmap <A-6> :ACSBfindsym grep <c-r>=expand("<cword>")<CR><CR>
nmap <A-7> :ACSBfindsym file <c-r>=expand("<cword>")<cr>
nmap <A-8> :ACSBfindsym inc <c-r>=expand("<cword>")<cr>
  if filereadable("cscope.out")
    cscope add cscope.out
  endif
endif

" Switch syntax highlighting on, when the terminal has colors
" Also switch on highlighting the last used search pattern.
if &t_Co > 2 || has("gui_running")
  syntax on
  set hlsearch
  colorscheme desert
endif

syntax on

if has("gui_running")
	set mouse=a
endif

if &term=="xterm"
     set t_Co=8
     set t_Sb=[4%dm
     set t_Sf=[3%dm
endif

if v:progname != "vimdiff"
  set number
endif

if v:progname =~? "evim"
  finish
endif

set guioptions-=T
set guioptions-=m

set incsearch
set autoindent
set smartindent
set noignorecase
set expandtab
set shiftwidth=2
set tabstop=2
set smarttab
set backspace=indent,eol,start
set tags=./tags,tags;/,/usr/include/tags
set winheight=999
set winminheight=0
set winminwidth=0
map  <C-tab> <C-S-down>
map  <C-S-tab> <C-S-up>
nmap Q :exe 'sts '.expand("<cword>")<CR>
nmap g} :if expand("<cword>")[0] > 'Z' \| exe 'sts '.toupper(expand("<cword>")[0]).(expand("<cword>")[1:]) \| else \| exe 'sts '.tolower(expand("<cword>")[0]).(expand("<cword>")[1:]) \| endif<CR>
"nmap <C-w><C-w> <C-w><C-w><C-w>\|<C-w>_
nmap <C-w><Up> <C-w><Up><C-w>_
nmap <C-w><Down> <C-w><Down><C-w>_
nmap <C-w><Left> <C-w><Left><C-w>\|
nmap <C-w><Right> <C-w><Right><C-w>\|
nmap ;; :buffers<CR>:
nmap ZZ ZZ<C-w>_
nmap <silent> <Leader>co :VCSVimDiff 1.1<CR>
nmap <silent> <Leader>ch :VCSVimDiff HEAD<CR>
nmap <Leader>cb :VCSVimDiff<Space>
nmap <Leader>cm :VCSAnnotate<Space>
augroup Binary
  au!
  au BufReadPre  *.bin let &bin=1
  au BufReadPost *.bin if &bin | %!xxd
  au BufReadPost *.bin set ft=xxd | endif
  au BufWritePre *.bin if &bin | %!xxd -r
  au BufWritePre *.bin endif
  au BufWritePost *.bin if &bin | %!xxd
  au BufWritePost *.bin set nomod | endif
augroup END
set laststatus=2
set statusline=%F%m%r,\ %Y,\ %{&fileformat},\ %{&fenc},%=%b,0x%B\ Ln:%l,\ Col:%c\ %p%%\ %LL
au BufRead foxyserver.log.*      if &fileencoding!='utf-8' | e ++enc=utf-8 |endif
au BufRead req_dump.log.*      if &fileencoding!='utf-8' | e ++enc=utf-8 |endif
"set tags=/home1/wuwl3/ff/fftag
"set tags+=/home1/wuwl3/work_debug/ff10/moztag
"set tags+=/home1/wuwl3/work_debug/lynemo/fftag
"set tags+=/home1/wuwl3/work_debug/lynemo/foxyserver3/ff_ext/exttag

"set tags+=/home1/wuwl3/new_project/ff10/moztag
"set tags+=/home1/wuwl3/new_project/lynemo/fftag
"set tags+=/home1/wuwl3/new_project/lynemo/foxyserver3/ff_ext/exttag
"set tags+=/home1/wuwl3/iphone_adap/lynemo/foxyserver3/ff_ext/exttag
"set tags+=/home1/wuwl3/gnome/gntag
"set tags+=/home1/wuwl3/test_gnome/libxml/xmltag
"set tags+=/home1/wuwl3/nginx/nginx-1.5.9/src/ngtag
"set tags+=/home1/wuwl3/performance_tune/my_64_bit_performance_tune/mozilla/mztag
"set tags+=/home1/wuwl3/performance_tune/my_64_bit_performance_tune/foxyserver3/ff_ext/exttag
set tags+=/home1/wuwl3/kernel/mozilla/mztag
set tags+=/home1/wuwl3/kernel/foxyserver3/ff_ext/exttag



" add
map ,hh :call SetColorColumn()<CR>
function! SetColorColumn()
  let col_num = virtcol(".")
  let cc_list = split(&cc, ',')
  if count(cc_list, string(col_num)) <= 0
  execute "set cc+=".col_num
  else
  execute "set cc-=".col_num
  endif
endfunction
