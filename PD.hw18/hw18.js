let contacts = [];
let mytable = document.getElementById("mytable");
function alertempty(item){
	let data = []
	if(item.uid==""){
		data.push('學號');
	}
	if(item.name==""){
		data.push('姓名');
	}
	if(item.phone==""){
		data.push('電話');
	}
	if(item.email==""){
		data.push('信箱');
	}
	if(data==""){
		return -1;
	}	
	else{
		data.push('為必填單位')
		data=data.join('');
		alert(data);
		return 1;
	}
}
function printdata(item){
	mytable.innerHTML="";
	let data = new Array();//let data = []
	data.push('<table id="mytable" width=60% border="1" align=center><caption>通訊錄</caption><tbody>');	
	data.push('<tr align=center><td width=20%>學號</td><td width=25%>姓名</td><td width=25%>電話</td><td width=30%>信箱</td></tr>')
	
	/*item.forEach(){
		data.push('<tr>');
		data.push('<td>' + item.uid + '</td>');
		data.push('<td>' + item.name + '</td>');
        data.push('<td>' + item.phone + '</td>');
        data.push('<td>' + item.mail + '</td>');
		data.push('</tr>');
	}*/

	for(let i=0;i<item.length;i++){ 
		data.push('<tr align=center>');
		data.push('<td>' + item[i].uid + '</td>');
		data.push('<td>' + item[i].name + '</td>');
        data.push('<td>' + item[i].phone + '</td>');
        data.push('<td>' + item[i].email + '</td>'); 
		data.push('</tr>');
	}
	
	data.push('</tbody></table>');

	mytable.innerHTML=data.join('');
}
function mymatch(item,id){
	for(let i=0;i<item.length;i++){
		if(item[i].uid == id){
			return i;
		} 
	}
	return -1;
}
function insert(form){  
	let data={
		uid: form.uid.value,
		name: form.name.value,
		phone: form.phone.value,
		email: form.email.value
	}	
	if(alertempty(data)==1){
		return;
	}	
	if(mymatch(contacts,form.uid.value)!=-1){
		alert('此學號已存在');
		return;
	}
    contacts.push(data);
	printdata(contacts);
}  
function mydelete(form){
	let data={
		uid: form.uid.value,
		name: form.name.value,
		phone: form.phone.value,
		email: form.email.value
	}
	if(alertempty(data)==1){
		return;
	}
	let idx = mymatch(contacts,form.uid.value);
	if(idx == -1){
		alert('Delete Error!此學號不存在');
		return;
	}
	else if(idx != -1){
		contacts.splice(idx,1);
	}
	printdata(contacts);
}
function update(form){
	let data={
		uid: form.uid.value,
		name: form.name.value,
		phone: form.phone.value,
		email: form.email.value
	}
	if(alertempty(data)==1){
		return;
	}
	let idx = mymatch(contacts,form.uid.value);
	if(idx == -1){
		alert('Update Error!此學號不存在');
		return;
	}
	else if(idx != -1){
		contacts.splice(idx,1,data);
	}
	printdata(contacts);
}
function mylist(){
	printdata(contacts);
}
function mysearch(word){
	let data = []
	
	for(let i=0;i<contacts.length;i++){
		if(contacts[i].uid.match(word)!=null || contacts[i].name.match(word)!=null || contacts[i].phone.match(word)!=null || contacts[i].email.match(word)!=null){
			data.push(contacts[i]);
		}
	}
	printdata(data);
	if(data.length==0){
		alert('No match!');
		mytable.innerHTML="";
	}
}
function ShowTime(){
　	var NowDate=new Date();
　	var h=NowDate.getHours();
　	var m=NowDate.getMinutes();
　	var s=NowDate.getSeconds();　
　	document.getElementById('showbox').innerHTML = h+'時'+m+'分'+s+'秒';
　	setTimeout('ShowTime()',1000);
}















