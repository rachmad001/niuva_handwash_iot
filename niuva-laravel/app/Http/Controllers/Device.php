<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;

class Device extends Controller
{
    public function index($device){
        $dataDev = file_get_contents($device);
        $data =  json_decode($dataDev, true);
        return $data;
    }

    public function addData(Request $req){
        $name = $req->input('device');
        $dataDev = file_get_contents($name);
        $data =  json_decode($dataDev, true);
        $data [] = array(
            'sabun' => $req->input('sabun'),
            'air' => $req->input('air'),
            'waktu' => array(
                'tanggal' => date("Y/m/d"),
                'jam' => date("H:i:s")
            )
        );
        $jsonFile = json_encode($data, JSON_PRETTY_PRINT);
        $device = file_put_contents($name, $jsonFile);
        if ($device){
            $state [] = array(
                'status' => 'success',
                'msg' => 'berhasil menambahkan data' 
            );
            return json_encode($state, JSON_PRETTY_PRINT);
        }
        else {
            $state [] = array(
                'status' => 'fail',
                'msg' => 'gagal menambahkan data' 
            );
            return json_encode($state, JSON_PRETTY_PRINT);
        }
    }

    public function login(Request $req){
        $username = $req->input('username');
        $password = $req->input('password');
        $users = DB::select('select * from login where username = ? AND password = ?', [$username, $password]);
        if (count($users) > 0){
            $data [] = array(
                'status' => 'success',
                'msg' => 'login success, welcome '.$users[0]->username,
                'dataDevice' => $users[0]->device
            );
            return $data;
        }
        else{
            $data [] = array(
                'status' => 'fail',
                'msg' => 'login fail',
                'dataDevice' => null
            );
            return $data;
        }
    }
}
