写在前面
=

本实例我们输入为个人成绩以及六级过线最低成绩425，来比较其是否过线，输入可在input.json中看到，电路可在InRange.circom文件中查询。

开发前提
=

本实例在Linux下进行，需预先安装Circom、Snarkjs依赖库，并推荐使用VS code环境开发。

__1.安装node__

`sudo apt update`

`sudo apt install nodejs npm -y`

__2.安装Rust__

`sudo apt install curl -y`

`sudo apt install cmake build-essential -y`

`curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh`

__3.安装Circom__

`git clone https://github.com/iden3/circom.git`

`cd circom`

`source $HOME/.cargo/env`

`cargo build --release`

`cargo install --path circom`

__4.安装Snarkjs__

`sudo npm install -g snarkjs`

项目实现
=

由于本实例已全部编译完毕，因此可直接执行证明电路部分第8步。

__编译电路__

`circom InRange.circom --r1cs --wasm --sym`

__计算证据__

`node generate_witness.js InRange.wasm input.json witness.wtns`

**__注意：此步需将所有文件放入同一文件夹内执行。__**

__证明电路__

1.`snarkjs powersoftau new bn128 12 pot12_0000.ptau -v`

2.`snarkjs powersoftau contribute pot12_0000.ptau pot12_0001.ptau --name="First contribution" -v`

3.`snarkjs powersoftau prepare phase2 pot12_0001.ptau pot12_final.ptau -v`

4.`snarkjs groth16 setup InRange.r1cs pot12_final.ptau multiplier2_0000.zkey`

5.`snarkjs zkey contribute multiplier2_0000.zkey multiplier2_0001.zkey --name="1st Contributor Name" -v\`

6.`snarkjs zkey export verificationkey multiplier2_0001.zkey verification_key.json`

7.`snarkjs groth16 prove multiplier2_0001.zkey witness.wtns proof.json public.json`

8.`snarkjs groth16 verify verification_key.json public.json proof.json`

运行截图
=

![image](https://github.com/CLiangH/Picture/blob/main/ZK6.png)
