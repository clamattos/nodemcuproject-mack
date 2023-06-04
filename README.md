# nodemcuproject-mack

# Projeto de Coleta de Dados de Temperatura e Umidade com NodeMCU 

Este projeto apresenta a implementação de um sistema de coleta de dados de temperatura e umidade utilizando a plataforma NodeMCU, juntamente com o Node-RED, uma ferramenta de automação e integração visual baseada em fluxos.

O NodeMCU é um dispositivo de baixo custo e fácil programação, baseado no microcontrolador ESP8266, que possui conectividade Wi-Fi integrada. 

O objetivo deste projeto é simular, em pequena escala, como essa implementação pode coletar dados com precisão, demonstrando a viabilidade e o potencial dessa tecnologia para aprimorar a coleta de dados de ambientes externos em escala.

## Recursos Utilizados

- Plataforma NodeMCU
- Sensor de temperatura e umidade (DHT11)
- LED vermelho
- Conexão Wi-Fi para comunicação com a Internet
- Broker MQTT (Message Queuing Telemetry Transport) para troca de mensagens
- Node-RED para criação de fluxos de automação e integração

## Funcionamento do Sistema

O sistema utiliza o NodeMCU para coletar dados de temperatura e umidade por meio de um sensor conectado à placa. O NodeMCU se conecta a uma rede Wi-Fi e estabelece uma conexão MQTT com um broker MQTT.

Em conjunto com o NodeMCU, o Node-RED é utilizado para criar fluxos de automação e integração visualmente. O Node-RED pode se inscrever no tópico MQTT onde as leituras de temperatura e umidade são publicadas pelo NodeMCU. Em seguida, o Node-RED pode processar esses dados e executar ações, como armazenar em um banco de dados, exibir em um painel de controle ou enviar notificações.

## Implementação e descrição do ambiente de desenvolvimento

A implementação do projeto envolve a programação do NodeMCU para coletar dados dos sensores de temperatura e umidade. Todas as vezes que a temperatura estiver fora de uma faixa específica, um LED deve acender para indicar condições inadequadas de temperatura. Os dados de umidade são apenas armazenados para análise posterior.

### NodeMCU:

- Configure a conexão Wi-Fi e as informações do broker MQTT no código do NodeMCU.
- Utilize a biblioteca MQTT (como a PubSubClient) para facilitar a comunicação MQTT.
- No código, realize a leitura dos dados do sensor de temperatura e umidade e publique as leituras no broker MQTT.

### Node-RED:

- Instale o Node-RED em seu ambiente de desenvolvimento.
- Crie um fluxo no Node-RED com um nó MQTT Subscriber para se inscrever no tópico MQTT onde as leituras de temperatura e umidade são publicadas.
- Adicione nós para processar os dados, como nós de armazenamento em banco de dados, visualização em um painel de controle ou envio de notificações.
- Conecte os nós de forma adequada para criar o fluxo de automação e integração desejado.

### Arduino IDE:

O ambiente de desenvolvimento conta com o uso de Arduino IDE e integração com Node-RED, como comentado. Sobre a IDE: 

- Arduino IDE: É a própria interface de desenvolvimento integrada (IDE) fornecida pela Arduino. É um software que permite escrever, compilar e carregar código nos dispositivos Arduino. Ele oferece uma interface amigável e simplificada para facilitar a programação.
- Editor de código: A Arduino IDE possui um editor de código onde você pode escrever seu programa. É um editor de texto básico.
- Gerenciador de bibliotecas: A Arduino IDE possui um gerenciador de bibliotecas embutido que permite buscar, instalar e atualizar bibliotecas adicionais.
- Compilador: Após escrever o código, você pode compilar o programa na Arduino IDE para verificar se não há erros de sintaxe ou outros problemas. O compilador converte o código em linguagem de máquina compreensível pelo microcontrolador.

### Hardware Utilizado:

1. NodeMCU ESP8266 ESP-12E

Placa de desenvolvimento baseada no microcontrolador ESP8266 com conectividade Wi-Fi integrada.
Possui GPIOs para conexão de periféricos externos.
Compatível com a plataforma Arduino IDE e linguagem Lua.
Tensão de operação: 4,5V - 9VDC.
Dimensões: 25mm(L) x 19mm(A) x 49mm(C).

2. Sensor de Umidade e Temperatura DHT11

Sensor de umidade e temperatura para integração com microcontroladores.
Faixa de medição de temperatura: 0º a 50ºC.
Faixa de medição de umidade: 20% a 80%.
Precisão de ±2ºC (temperatura) e ±5% (umidade).
Taxa de amostragem: 1 leitura por segundo.

3. Resistor de 10K

Resistor utilizado para controle de corrente em circuitos eletrônicos.
Valor: 10.000 ohms.

4. Cabos Jumper Macho-Fêmea

Cabos jumper para conexões temporárias em circuitos eletrônicos.
Conector macho em uma extremidade e conector fêmea na outra.
Comprimento: 20cm.
Kit com 40 peças.

5. Atuador LED Difuso Vermelho

LED difuso de cor vermelha para indicar ação relacionada à temperatura.
Utilizado para sinalização quando a temperatura está na faixa não ideal.

## Pré-requisitos do projeto 

Este projeto utiliza o AWS IoT Core e o DynamoDB para ingestão e persistência de dados. Para subir cada um dos componentes, é necessário ter uma conta AWS. Com uma conta em execução, siga o passo-a-passo: 

Criação de "Thing" no IoT Core:

1. Clique em "Gerenciar" no painel de navegação à esquerda e selecione "Things"
2. Clique em criar para criar um novo Thing
3. Insira um nome para o seu Thing
4. Preencha os detalhes necessários
6. Adicione um certificado para autenticação do Thing. Escolha criar um novo certificado ou usar um certificado existente e siga as instruções para adicionar o certificado.

Criação de tabela no DynamoDB:

1. Clique em "Criar tabela" para iniciar o processo de criação de uma nova tabela
2. Insira um nome para a tabela no campo "Nome da tabela"
3. Defina a chave primária da tabela. A chave primária é usada para identificar exclusivamente cada item na tabela
4. Especifique o tipo de dado para a chave primária (por exemplo, número, string)
5. Defina outras configurações da tabela, como capacidade de leitura/gravação provisionada ou capacidade sob demanda
6. Clique em "Criar tabela" para criar a tabela com as configurações especificadas

Criação de regra de conexão com DynamoDB: 

1. Clique em "Gerenciar" no painel de navegação à esquerda e selecione "Rules" 
2. Clique em criar uma nova regra
3. Insira um nome para a sua regra
4. Na seção "Selecionar ação", clique em adicionar ação
5. Selecione "Enviar mensagem para DynamoDB" 
6. Selecione a tabela do DynamoDB onde deseja gravar os dados
7. Defina a chave primária (partition key)
8. Mapeie os campos da mensagem MQTT para os atributos da tabela do DynamoDB

## Como Utilizar o Projeto

1. Clone este repositório em sua máquina local.

```shell
git clone https://github.com/clamattos/nodemcu-node-red-coleta-dados-temperatura-umidade.git
```

2. Faça as devidas conexões do sensor de temperatura e umidade ao NodeMCU. Consulte o esquemático fornecido no repositório para obter informações sobre as conexões corretas. 

3. Configure um arquivo chamado Secrets.h, em que você deve inserir o seu SSID, WIFI_PASSWORD, THINGNAME, MQTT_HOST, CERTIFICATES.

4. Carregue o código no NodeMCU por meio da porta USB.

5. Inicie o Node-RED em seu ambiente de desenvolvimento.

6. Importe o fluxo fornecido no repositório para o Node-RED.

7. Conecte o NodeMCU à rede Wi-Fi e ao broker MQTT.

8. Execute o fluxo no Node-RED para iniciar a coleta de dados, visualização e automação conforme desejado.

Acompanhe as leituras de temperatura e umidade no IoT Core por meio do seguinte procedimento: 

1. Clique em MQTT Test Client e selecioner Inscrever-se em um tópico 
2. Coloque o nome do tópico e clique em inscrever-se 

Ao configurar o Node-RED, você também pode acessar o portal de dashboards por: 127.0.0.1:1880/ui

### Documentações auxiliares

NodeMCU: https://nodemcu.readthedocs.io/en/release/

Core-doc ESP8266: https://arduino-esp8266.readthedocs.io/en/latest/

Arduino IDE: https://docs.arduino.cc/software/ide-v1/tutorials/arduino-ide-v1-basics

Node-RED: https://nodered.org/docs/

MQTT info: https://mqtt.org/

MQTT broker (IoT Core): https://docs.aws.amazon.com/iot/index.html

DynamoDB: https://docs.aws.amazon.com/dynamodb/index.html

