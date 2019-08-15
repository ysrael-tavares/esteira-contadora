import json

from flask import Flask, render_template, redirect, request
from flask_socketio import SocketIO, send, emit
from flask_cors import CORS

app = Flask(__name__)
socketio = SocketIO(app)
CORS(app)

estado = {
    "ESTEIRA" :0 ,
	"ITENS" : 0 ,
	"RESET" : 0
}
	
@app.route("/")
def rota_inicial():
    return render_template("index.html")

@app.route("/upload",methods = ["POST"])
def rota_upload():
    mensagem = request.get_json()
    socketio.emit("atualiza",mensagem)
    return "200"
	
@app.route("/download", methods=['GET'])
def rota_download():
    global estado
    return json.dumps(estado)

@socketio.on("ligarEsteira")
def ligar_esteira():
    global estado
    estado["ESTEIRA"] = 0
	
@socketio.on("desligarEsteira")
def desligar_esteira():
    global estado
    estado["ESTEIRA"] = 1
	
@socketio.on("zerarItens")
def zera_itens():
    global estado
    estado["RESET"] = 1   

if __name__ == "__main__":
    app.run("0.0.0.0",port=8080)