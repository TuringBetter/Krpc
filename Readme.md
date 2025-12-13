# 环境配置
## 1. 安装基础环境
```shell
sudo apt-get install -y wget cmake build-essential unzip libboost-all-dev libssl-dev
```
## 2. 安装Muduo库
### 2.1 克隆仓库
```shell
git clone https://github.com/chenshuo/muduo.git
```
### 2.2 编译Muduo
```shell
cd muduo && mkdir build && cd build && cmake .. && make
```
### 2.3 安装Muduo
（~/muduo/build$）
```shell
sudo make install
```
## 3. 配置zookeeper
## 3.1 安装zookeeper
```shell
sudo apt install zookeeperd
```
## 3.2 安装 Zookeeper 开发库
```shell
sudo apt install libzookeeper-mt-dev
```
## 3.3 启用zookeeper
```shell
sudo systemctl  start zookeeper
```
## 4. 安装protobuf
```shell
sudo apt-get install protobuf-compiler libprotobuf-dev  
```
## 5. 安装glog
```shell
sudo apt-get install libgoogle-glog-dev libgflags-dev
```
## 6. 编译Krpc
```shell
第一步：进入到krpc文件
cd Krpc

第二步：生成项目可执行程序
mkdir build && cd build && cmake .. && make -j${nproc}

第三步：然后进入到example文件夹下，找到user.proto文件执行以下命令,会生成user.pb.h和user.pb.cc：
cd example
protoc --cpp_out=. user.proto

第四步：进入到src文件下，找到Krpcheader.proto文件同样会生成如上pb.h和pb.cc文件
cd src
protoc --cpp_out=. Krpcheader.proto

第五步：进入到bin文件夹下,分别运行./server和./client，即可完成服务发布和调用。
进入bin文件:
cd bin

运行server可执行程序:
./server -i ./test.conf

运行client可执行程序：
./client -i ./test.conf
```