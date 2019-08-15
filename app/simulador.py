import requests

while(True):
    valor = int(input("Informe um valor: "))
    r = requests.post( "http://teste-esteira.herokuapp.com/upload" , json = {"ITENS":valor} )
    print(r.status_code)

    r = requests.get( "http://teste-esteira.herokuapp.com/download" )
    print(r.json())
