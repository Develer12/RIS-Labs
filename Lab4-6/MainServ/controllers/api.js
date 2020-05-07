const express = require('express');
const Route = express.Router();
const rt = require(__dirname + '/api/service');


Route.use('/', rt);


module.exports = Route;
