const express = require('express');
const Route = express.Router();
const db = require(__dirname + '/../../models/DB/DB_Handler');
const DB = new db();
const request = require('request-promise');

Route.post('/', (req, res) =>{
    DB.insert(req.body)
    .catch(err => {
        res.statusCode = 400;
        res.json({error: err.toString()});
    });
});

Route.post('/gen', (req, res) =>{
    DB.insertNew()
    .catch(err => {
        res.statusCode = 400;
        res.json({error: err.toString()});
    });
});

Route.get('/service', (req, res) =>{
    DB.getService()
    .then(records =>{
        res.json(records.recordset);
    })
    .catch(err => {
        res.statusCode = 400;
        res.json({error: err.toString()});
    });
});

Route.get('/alive/:id', (req, res) =>{
    request({
        method: 'GET',
        uri: `http://localhost:${3000 + Number(req.params.id)}/api/check`,
        json: true
    })
    .then((response) => {
        if(response){
            res.send(`It's ALIVE!!!!`)
        }
        else{
            res.send(`No answer(`)
        }
    })
    .catch((err) => {
        res.send(`Serv is DEAD`);
    });
});

Route.get('/check', (req, res) =>{
    res.json({answer: 1});
});

Route.get('/watt', (req, res) =>{
    DB.getAll()
    .then(records =>{
        res.json(records.recordset);
    })
    .catch(err => {
        res.statusCode = 400;
        res.json({error: err.toString()});
    });
});

Route.get('/watt/:id', (req, res) =>{
    DB.getbyId(req.params.id)
    .then(records =>{
        res.json(records.recordset);
    })
    .catch(err => {
        res.statusCode = 400;
        res.json({error: err.toString()});
    });
});

Route.get('/watt/date/max/:id', (req, res) =>{
    DB.getMaxDate(req.params.id)
    .then(records =>{
        res.json(records.recordset);
    })
    .catch(err => {
        res.statusCode = 400;
        res.json({error: err.toString()});
    });
});

Route.get('/watt/date/:id', (req, res) =>{
    DB.getFromDate(req.params.id, req.body.date)
    .then(records =>{
        res.json(records.recordset);
    })
    .catch(err => {
        res.statusCode = 400;
        res.json({error: err.toString()});
    });
});


module.exports = Route;
