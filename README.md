# node-webkit addon sample
==========================
## 环境
### 1.node v0.12.4
### 2.node-webkit v0.12.2
### 3.vs2010+
## 编译   
### 1.安装nw-gyp
npm install -g nw-gyp
### 2.编译
在程序目录下执行
nw-gyp configure --runtime=node-webkit --target=0.12.2
nw-gyp build
## 测试
在程序目录下，执行（注意有一个点）
nw .
## 用node.js调试源程序
npm install -g node-gyp
node-gyp configure
node-gyp build
node index.js
## 参考
https://github.com/joyent/node/blob/v0.12/doc/api/addons.markdown