# robocon2017
高専ロボコン2017
今年のメインプログラム開発用のrepository

masterはmegaそれ以外は全部nano

##各プログラムの役割
###Master
統括処理。PropoTermからのデータを受信し、操縦者の操作に応じた移動計算、攻撃処理を行う

###PropoTerm
プロポレシーバの信号を計測し、加工してMasterへ送る

###MotorTerm
モータの出力処理。Masterからのデータに応じてPWM出力を行う。おろっちのステアリングのP制御もここでやってる

###ServoTerm
サーボの出力処理。Masterからのデータに応じてサーボ出力を行う。

