const express = require('express'); 
const path =require('path');   
const app = express(); 

var bodyParser = require("body-parser");
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

const router = express.Router(); 

app.use(express.static(__dirname));
let resultado; 

router.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/index.html'));
  //__dirname : It will resolve to your project folder.
});

router.post('/resultado', (req, res) => {
  res.header("Access-Control-Allow-Origin", "*");
  //console.log(req.body); 
  resultado = req.body;
  console.log(resultado);
});

router.get('/esp/resultado', (req, res) => {
  res.send(resultado);
  //resultado = ""
})

router.get('/limpa/dados', (req, res) => {
  resultado = ""
  res.send("Limpei")
})

app.use('/', router); 
app.listen(3000, () => {
  console.log('Node rodando em: http://localhost:3000/')
}); 

