var w;
var filecount = 0;
$(document).ready(function() {
		$(".obutton").hide();
		
	$("#ClearLocal").click(function(event)
	{
		localStorage.clear();
	});
	$("#ClearAll").click(function(event)
	{
		$("ul#list").html("");
		$(".summary").html("");
		$("ul").html("");
		$(".obutton").hide();
	});
	$("#button4").click(function(event)
	{
		var localData = localStorage['files'];
		var pdata = JSON.parse(localData);
		$("ul#list").html("");
		filecount = 0;
		$.each(pdata,function(index,entry)
		{
			filecount++;
			$("ul#list").append('<li>'+entry.item+'</li>');
		});
		$("#sum1").html(filecount+" Files and Folders found");
		var localData = localStorage['procs'];
		var pdata = JSON.parse(localData);
		$("ul#list2").html("");
		var proccount = 0;
		$.each(pdata,function(index,entry)
		{
			proccount++;
			$("ul#list2").append('<li>'+entry.item+'</li>');
		});
		$("#sum2").html(proccount+" processes found ");
		
		var localData = localStorage['tcp4'];
		var pdata = JSON.parse(localData);
		$("ul#t4list").html("");
		var portcount = 0;
		$.each(pdata,function(index,entry)
		{
			portcount++;
			$("ul#t4list").append('<li>'+entry.item+'</li>');
		});
		$("#sumt4").html(portcount+" new ports found ");
		
		var localData = localStorage['udp4'];
		var pdata = JSON.parse(localData);
		$("ul#u4list").html("");
		var portcount = 0;
		$.each(pdata,function(index,entry)
		{
			portcount++;
			$("ul#u4list").append('<li>'+entry.item+'</li>');
		});
		$("#sumu4").html(portcount+" new ports found ");
		
		var localData = localStorage['tcp6'];
		var pdata = JSON.parse(localData);
		$("ul#t6list").html("");
		var portcount = 0;
		$.each(pdata,function(index,entry)
		{
			portcount++;
			$("ul#t6list").append('<li>'+entry.item+'</li>');
		});
		$("#sumt6").html(portcount+" new ports found ");
		
		var localData = localStorage['udp6'];
		var pdata = JSON.parse(localData);
		$("ul#u6list").html("");
		var portcount = 0;
		$.each(pdata,function(index,entry)
		{
			portcount++;
			$("ul#u6list").append('<li>'+entry.item+'</li>');
		});
		$("#sumu6").html(portcount+" new ports found ");
	//	alert("parsed","test");
	});
	
	addToList = function(data)
	{
	//	alert("Success", "Test");
		var jsondata = JSON.stringify(data);
		filecount = 0;
		localStorage.removeItem("files");
		localStorage['files'] = jsondata;
		$("ul#list").html("");
		
		$.each(data,function(index,entry)
		{
			filecount++;
			if(!$("#chkbox").attr('checked'))
			{
				$("ul#list").append('<li>'+entry.item+'</li>');
				
			}
			
		});
		
		$("#sum1").html(filecount+" Files and Folders found.");
		if(filecount!=0)
		{
		$("#sum1").append("<br/>Add to the database? ");
		$("#yesbutton1").show();
		$("#nobutton1").show();
		}
	}
	$("#nobutton1").click(function(event)
	{
		$("#sum1").html("Files and folders not added");
		$("#yesbutton1").hide();
		$("#nobutton1").hide();
	});
	$("#nobutton2").click(function(event)
	{
		$("#sum2").html("Processes not added to the database");
		$("#yesbutton2").hide();
		$("#nobutton2").hide();
	});
	$("#nobuttont4").click(function(event)
	{
		$("#sumt4").html("Ports not added");
		$("#yesbuttont4").hide();
		$("#nobuttont4").hide();
	});
	$("#nobuttonu6").click(function(event)
	{
		$("#sumu6").html("Ports not added");
		$("#yesbuttonu6").hide();
		$("#nobuttonu6").hide();
	});
	$("#nobuttonu4").click(function(event)
	{
		$("#sumu4").html("Ports not added");
		$("#yesbuttonu4").hide();
		$("#nobuttonu4").hide();
	});
	$("#nobuttont6").click(function(event)
	{
		$("#sumt6").html("Ports not added");
		$("#yesbuttont6").hide();
		$("#nobuttont6").hide();
	});
	$("#yesbutton1").click(function(event)
	{
	//	alert("sending json data", "Test");
		var path = '';
		  var input = $("#textbox1").val();
		  path = path + "/ajax/savefiles";
		  $.ajax({
			dataType: 'text',
			url: '/ajax/savefiles',
			data: "savefiles",
			type: "Post",
			success: filesadded,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});

	});
	
	$("#yesbutton2").click(function(event)
	{
	//	alert("sending json data", "Test");
		  var input = $("#textbox1").val();

		  $.ajax({
			dataType: 'text',
			url: '/ajax/saveprocs',
			data: "saveprocs",
			type: "Post",
			success: procsadded,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});

	});
	$("#yesbuttont4").click(function(event)
	{
	//	alert("sending json data", "Test");

		  $.ajax({
			dataType: 'text',
			url: '/ajax/savet4',
			data: "savet4",
			type: "Post",
			success: t4added,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});

	});
	$("#yesbuttonu4").click(function(event)
	{
	//	alert("sending json data", "Test");

		  $.ajax({
			dataType: 'text',
			url: '/ajax/saveu4',
			data: "saveu4",
			type: "Post",
			success: u4added,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});

	});
	$("#yesbuttont6").click(function(event)
	{
	//	alert("sending json data", "Test");

		  $.ajax({
			dataType: 'text',
			url: '/ajax/savet6',
			data: "savet6",
			type: "Post",
			success: t6added,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});

	});
	$("#yesbuttonu6").click(function(event)
	{
	//	alert("sending json data", "Test");

		  $.ajax({
			dataType: 'text',
			url: '/ajax/saveu6',
			data: "saveu6",
			type: "Post",
			success: u6added,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});

	});
	procsadded = function(data)
	{
		$("#sum2").html("Processes added successfully");
		$("#yesbutton2").hide();
		$("#nobutton2").hide();
	}
	t4added = function(data)
	{
		$("#sumt4").html("Ports added successfully");
		$("#yesbuttont4").hide();
		$("#nobuttont4").hide();
	}
	u4added = function(data)
	{
		$("#sumu4").html("Ports added successfully");
		$("#yesbuttonu4").hide();
		$("#nobuttonu4").hide();
	}
	t6added = function(data)
	{
		$("#sumt6").html("Ports added successfully");
		$("#yesbuttont6").hide();
		$("#nobuttont6").hide();
	}
	u6added = function(data)
	{
		$("#sumu6").html("Ports added successfully");
		$("#yesbuttonu6").hide();
		$("#nobuttonu6").hide();
	}
	filesadded = function(data)
	{
		$("#sum1").html("Files and folders added successfully");
		$("#yesbutton1").hide();
		$("#nobutton1").hide();
	}
	addToList2 = function(data)
	{
		//alert("Proc Success", "Test");
		var jsondata = JSON.stringify(data);
		var proccount = 0;
		localStorage.removeItem("procs");
		localStorage['procs'] = jsondata;
		$("ul#list2").html("");
		
		$.each(data,function(index,entry)
		{
			proccount++;
			if(!$("#chkbox").attr('checked'))
			{
				$("ul#list2").append('<li>'+entry.item+'</li>');
				
			}
			
		});
		
		$("#sum2").html(proccount+" processes found");
		if(proccount!=0)
		{
		$("#sum2").append("<br/>Add to the database? ");
		$("#yesbutton2").show();
		$("#nobutton2").show();
		}
	}
	addToTcp4 = function(data)
	{
		//alert("Proc Success", "Test");
		var jsondata = JSON.stringify(data);
		var portcount = 0;
		localStorage.removeItem("tcp4");
		localStorage['tcp4'] = jsondata;
		$("ul#t4list").html("");
		
		$.each(data,function(index,entry)
		{
			portcount++;
			if(!$("#chkbox").attr('checked'))
			{
				$("ul#t4list").append('<li>'+entry.item+'</li>');
				
			}
			
		});
		
		$("#sumt4").html(portcount+" new ports found");
		if(portcount!=0)
		{
		$("#sumt4").append("<br/>Add to the database? ");
		$("#yesbuttont4").show();
		$("#nobuttont4").show();
		}
	}
	addToTcp6 = function(data)
	{
		//alert("Proc Success", "Test");
		var jsondata = JSON.stringify(data);
		var portcount = 0;
		localStorage.removeItem("tcp6");
		localStorage['tcp6'] = jsondata;
		$("ul#t6list").html("");
		
		$.each(data,function(index,entry)
		{
			portcount++;
			if(!$("#chkbox").attr('checked'))
			{
				$("ul#t6list").append('<li>'+entry.item+'</li>');
				
			}
			
		});
		
		$("#sumt6").html(portcount+" new ports found");
		if(portcount!=0)
		{
		$("#sumt6").append("<br/>Add to the database? ");
		$("#yesbuttont6").show();
		$("#nobuttont6").show();
		}
	}
	addToUdp4 = function(data)
	{
		//alert("Proc Success", "Test");
		var jsondata = JSON.stringify(data);
		var portcount = 0;
		localStorage.removeItem("udp4");
		localStorage['udp4'] = jsondata;
		$("ul#u4list").html("");
		
		$.each(data,function(index,entry)
		{
			portcount++;
			if(!$("#chkbox").attr('checked'))
			{
				$("ul#u4list").append('<li>'+entry.item+'</li>');
				
			}
			
		});
		
		$("#sumu4").html(portcount+" new ports found");
		if(portcount!=0)
		{
		$("#sumu4").append("<br/>Add to the database? ");
		$("#yesbuttonu4").show();
		$("#nobuttonu4").show();
		}
	}
	addToUdp6 = function(data)
	{
		//alert("Proc Success", "Test");
		var jsondata = JSON.stringify(data);
		var portcount = 0;
		localStorage.removeItem("udp6");
		localStorage['udp6'] = jsondata;
		$("ul#u6list").html("");
		
		$.each(data,function(index,entry)
		{
			portcount++;
			if(!$("#chkbox").attr('checked'))
			{
				$("ul#u6list").append('<li>'+entry.item+'</li>');
				
			}
			
		});
		
		$("#sumu6").html(portcount+" new ports found");
		if(portcount!=0)
		{
		$("#sumu6").append("<br/>Add to the database? ");
		$("#yesbuttonu6").show();
		$("#nobuttonu6").show();
		}
	}
	$("#button1").click(function (event) 
	{
		//alert("sending json data", "Test");
		  var path = '';
		  var input = $("#textbox1").val();
		  path = path + "/ajax/msg";
		  $.ajax({
			dataType: 'jsonp',
			url: '/ajax/filemsg',
			data: {text: input},
			type: "Post",
			success: addToList,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});
		$.ajax({
			dataType: 'jsonp',
			url: '/ajax/procmsg',
			data: {text: input},
			type: "Post",
			success: addToList2,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});
		$.ajax({
			dataType: 'jsonp',
			url: '/ajax/tcp4',
			data: {text: input},
			type: "Post",
			success: addToTcp4,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});
		$.ajax({
			dataType: 'jsonp',
			url: '/ajax/tcp6',
			data: {text: input},
			type: "Post",
			success: addToTcp6,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});
		$.ajax({
			dataType: 'jsonp',
			url: '/ajax/udp4',
			data: {text: input},
			type: "Post",
			success: addToUdp4,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});
		$.ajax({
			dataType: 'jsonp',
			url: '/ajax/udp6',
			data: {text: input},
			type: "Post",
			success: addToUdp6,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});
		
		
     //   alert("Json message sent", "Test");
	});
	$("#button2").click(function (event) {
	//	alert("sending json data", "Test");
		  var path = '';
		  path = path + "/ajax/msg";
		  $.ajax({
			dataType: 'jsonp',
			url: '/ajax/jmsg',
			data: {text:"Aditya"},
			type: "Post",
			success: function(data,textstatus,jqXHR) {
			$("#jsonmsg").html("Message received: " + data);
			  alert("Success","Test");
			},
			error: function(data) {
			  alert("Error", "Test");
			},
		});
      //  alert("Json message sent", "Test");
	});
	$("#button3").click(function (event) {
       //   alert("making ajax call", "Test");
		  var path = '';
		  var input = $("#textbox1").val();

		  path = path + "/ajax/msg";
		  $.ajax({
			dataType: 'text',
			url: '/ajax/msg',
			data: input,
			type: "Post",
			success: function(data,textstatus,jqXHR) {
			var node = document.getElementById("ajaxMsg");
			node.innerHTML = data;
			  alert("Success","Test");
			},
			error: function(data) {
			  alert("Error", "Test");
			},
		});
	});
	$("#button3a").click(function(event)
	{
		$("#list").html("");
	});
	$("#button5").click(function(event)
	{
		localStorage.clear();
	});
	$("#button5a").click(function(event)
	{
		$("#list2").html("");
	});
	$("#button6a").click(function(event)
	{
		w.terminate();
	});
	$("#button6").click(function(event)
	{
		w=new Worker("worker.js");
		w.onmessage = function (event) {

		$("#list3").append('<li>'+event.data+'</li>');
    };
	});
});

