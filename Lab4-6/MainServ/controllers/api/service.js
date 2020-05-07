const express = require('express');
const Route = express.Router();
const db = require(__dirname + '/../../models/DB/DB_Handler');
const DB = new db();
const {DBid} = require(__dirname + '/../../config');

Route.post('/', (req, res) =>{
    DB.insert(req.body)
    .catch(err => {
        res.statusCode = 400;
        res.json({error: err.toString()});
    });
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

Route.get('/watt/date', (req, res) =>{
    DB.getbyDate(req.body.date)
    .then(records =>{
        res.json(records.recordset);
    })
    .catch(err => {
        res.statusCode = 400;
        res.json({error: err.toString()});
    });
});


module.exports = Route;
