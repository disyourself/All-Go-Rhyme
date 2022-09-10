
call plug#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
"Plugin 'VundleVim/Vundle.vim'
Plug 'ycm-core/YouCompleteMe'
Plug 'scrooloose/nerdtree'  "目录树
Plug 'frazrepo/vim-rainbow' "彩虹括号
Plug 'tpope/vim-surround'
Plug 'jiangmiao/auto-pairs' "括号配对

" Theme
Plug 'joshdick/onedark.vim'
Plug 'rakr/vim-one'


Plug 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plug 'L9'

Plug 'git://git.wincent.com/command-t.git'
"Plug 'file:///home/gmarik/path/to/plugin'
" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
Plug 'rstacruz/sparkup', {'rtp': 'vim/'}
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plug 'ascenator/L9', {'name': 'newL9'}

" All of your Plugins must be added before the following line
call plug#end()            " required


"Credit joshdick "Use 24-bit (true-color) mode in Vim/Neovim when outside tmux.
"If you're using tmux version 2.2 or later, you can remove the outermost $TMUX check and use tmux's 24-bit color support
"(see < http://sunaku.github.io/tmux-24bit-color.html#usage > for more information.)
if (empty($TMUX))
  if (has("nvim"))
    "For Neovim 0.1.3 and 0.1.4 < https://github.com/neovim/neovim/pull/2198 >
    let $NVIM_TUI_ENABLE_TRUE_COLOR=1
  endif
  "For Neovim > 0.1.5 and Vim > patch 7.4.1799 < https://github.com/vim/vim/commit/61be73bb0f965a895bfb064ea3e55476ac175162 >
  "Based on Vim patch 7.4.1770 (`guicolors` option) < https://github.com/vim/vim/commit/8a633e3427b47286869aa4b96f2bfc1fe65b25cd >
  " < https://github.com/neovim/neovim/wiki/Following-HEAD#20160511 >
  if (has("termguicolors"))
    set termguicolors
  endif
endif
" Status Tab
set laststatus=2
set statusline=%1*\%<%.50F\             "显示文件名和文件路径 (%<应该可以去掉)
set statusline+=%=%2*\%y%m%r%h%w\ %*        "显示文件类型及文件状态
set statusline+=%3*\%{&ff}\[%{&fenc}]\ %*   "显示文件编码类型
set statusline+=%4*\ row:%l/%L,col:%c\ %*   "显示光标所在行和列
set statusline+=%5*\%3p%%\%*            "显示光标前文本所占总文本的比例



" 			YCM
" Let clangd fully control code completion
"let g:ycm_clangd_uses_ycmd_caching = 0
" Use installed clangd, not YCM-bundled clangd which doesn't get updates.
let g:ycm_clangd_binary_path = "/usr/sbin/clangd"
" 允许自动加载.ycm_extra_conf.py，不再提示                         
let g:ycm_confirm_extra_conf=0    
" 补全功能在注释中同样有效                                         
let g:ycm_complete_in_comments=1    
" 开启tags补全引擎                                                 
let g:ycm_collect_identifiers_from_tags_files=1   
let g:ycm_goto_buffer_command = 'horizontal-split' " 跳转打开上下分屏
let g:rainbow_active=1

let g:ycm_enable_inlay_hints=1


syntax on
syntax enable
set shiftwidth=4
set tabstop=4
set cindent
set number
set path+=/usr/local/include/
set foldmethod=manual
set autoindent
set showcmd

filetype indent on

" Command Line View
set wildmode=list:full 
"set wildmenu

set background=dark " for the dark version
" set background=light " for the light version
colorscheme onedark


" clang jump
map <C-j> :YcmCompleter GoToDefinitionElseDeclaration<CR>
" Neartree
map <F3> :NERDTreeMirror<CR>
map <F3> :NERDTreeToggle<CR>
noremap <C-d> :call SavedAndOpenTerm()<CR>
noremap <F4> :YcmCompleter GoToDocumentOutline<CR>
noremap <C-s> :call Save_Format()<CR>

def Save_Format() 
	:w
	:YcmCompleter Format
enddef

def SavedAndOpenTerm()
	:w
	:bo term ++rows=10
enddef



" Status Line Color
hi User1 cterm=none ctermfg=27 ctermbg=0 
hi User2 cterm=none ctermfg=208 ctermbg=0
hi User3 cterm=none ctermfg=169 ctermbg=0
hi User4 cterm=none ctermfg=100 ctermbg=0
hi User5 cterm=none ctermfg=green ctermbg=0

