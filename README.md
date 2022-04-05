# Trabalho 2 de FSE

## Servidor Central

O servidor central foi implementado em Node.js e é o serviço que recebe, via socket, todas as atualizações de todos os sistemas distribuidos e disponibiliza um dashboard para visualização de todas as informações.

Esse serviço necessita de 2 portas, uma para o socket e outra para o acesso ao dashboard. Essas portas são configuradas no `.env` e no `docker-compose.yml`, com a seguinte configuração:
- Porta do socket: `10005`
- Porta do dashboard: `3002`

Para rodar o serviço utilize o comando abaixo:

```sh
docker-compose up
```

Com o servidor central rodando o dashboard estará disponivel em `localhost:3002`.

*Observação: Durante o desenvolvimento foi feito o tunelamento da porta `3002` por ssh para fazer o acesso ao dashboard. Para isso foi utilizado o comando abaixo:*

```sh
ssh -L 3002:localhost:3002 [usuário]@[host] -p [porta do ssh]
```
## Servidor Distribuido

O servidor distribuido foi desenvolvido em C e gerencia o andar do prédio com todos os sensores. Utiliza de um arquivo de configuração `config.json` para instanciar os valores das variáveis de configuração.

Para rodar esse serviço rode os comandos abaixo dentro da pasta `distributed_server/`:

```sh
make
make run
```
