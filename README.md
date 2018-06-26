# Projeto-3: "qtsupervisory"
Projeto para avaliação da 3ª unidade de programação avançada
## Projeto TcpProducer
Este projeto é sobre um produtor de dados para um servidor, possui 7 classes que serão usadas como slot  no Qt e uma função. O usuário deve digitar o IP da maquina que quer se conectar e desconectar,escolher a faixa de valores dos dados,iniciar e parar a transmissão e o tempo de envio de dados 
### Public Slots
1. void tcpConnect()
2. void tcpDisconnect()
3. void start()
4. void setMinimo(int _minimo)
5. void setMaximo(int _maximo)
6. void setTiming(int _timing)
7. void stopTransmissao()
#### void tcpConnect()
Esta função conecta o socket ao servidor, através do IP dado pelo usuário. Ela chama a função *connectToHost* da biblioteca do Qt.
#### void tcpDisconnect()
Esta função desconecta o socket do servidor. Ela chama a função *connectToHost* da biblioteca do Qt.
#### void start()
Esta função inicializa a transmissão dos sets ao servidor, contendo a hora mais os numeros da faixa (minimo,maximo) determinada pelo usuário.
#### void setMinimo(int _minimo)
Esta função recebe o valor minimo escolhido pelo usuário
#### void setMaximo(int _maximo)
Esta função recebe o valor maximo escolhido pelo usuário
#### void setTiming(int _timing)
Esta função recebe o valor do tempo(timing) escolhido pelo usuário
#### void stopTransmissao()
Esta função para a transmissão de sets. Ela chama a função *void QObject::killTimer(int id)* do Qt que recebe um inteiro timerID com a identificação do tempo para mata o timer.
### Public Functions
1. void timerEvent(QTimerEvent *event)
#### void timerEvent(QTimerEvent *event) 
Esta função é do Qt, é um temporizador, nela é chamada a função start() e passado o identificador do timer através da função *timerId()*. A qual é uma função do ponteiro event. No construtor da mainWindow é chamado a função *startTimer(timing*1000)* que recebe o tempo escolhido pelo usuario.
### Variáveis
1. **maximo**: variavel privada inteira para receber o valor maximo da faixa 
2. **minimo**: variavel privada inteira para receber o valor minimo da faixa 
3. **timing**: variavel privada inteira para receber o valor do tempo escolhido pelo usuário
4. **timerID**: variavel globar inteira que receber o identificador do temporizador
## Projeto TcpConsumer
Este projeto é sobre um consumidor de dados que recebe os dados produzidos no servidor indicado e mostra um gráfico com esses dados.
Contém 5 public slots, e 2 funções.
### Public Slots
1. **void Item(QListWidgetItem *item)**: recebe o texto do listwidget;
2. **void getData()**: aciona o get no servidor e recebe os dados;
3. **void tcpConnect():** conecta ao IP do servidor indicado pelo usuário;
4. **void tcpDisconnect():** desconecta o IP;
5. **void upgrade():** atualiza a lista dos IPs.
### Public Functions:
1. **void timeStamp():** converte de Milisegundos Epoch para inteiro;
2. **void listData():** Aciona o list no servidor.
### Variáveis
1. **std::vector <qint64> tempo**:vetor do tipo qint64 para receber o tempo em Milisegundos Epoch;
2. **std::vector <int> valores**: vetor para receber os valores inteiros;
3. **QString itemDaLista**: recebe o texto do listWidget.
