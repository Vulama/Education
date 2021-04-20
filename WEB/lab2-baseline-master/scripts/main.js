let bucket = [];
let data =[];

if(!window.localStorage.arr){
    window.localStorage.setItem("arr", bucket);
}
if(!window.localStorage.counter){
    window.localStorage.setItem("counter", 0);
}
if(!window.localStorage.data){
    window.localStorage.setItem("data", data);
}


let listId = [];
if(!window.localStorage.listID){
    window.localStorage.setItem("ids", listId);
}