var i=0;

function timedCount()
{
i=i+1;
postMessage(i);
setTimeout("timedCount()",500);
}

timedCount(); 
/*
function getRepeatList
{
	var path = '';
		  path = path + "/ajax/msg";
		  $.ajax({
			dataType: 'jsonp',
			url: '/ajax/listmsg',
			data: "list",
			type: "Post",
			success: addToWorkerList,
			error: function(data) 
			{
			  alert("Error", "Test");
			},
		});
}
getRepeatList();
addToWorkerList = function(data)
	{
	//	alert("Success", "Test");
		postMessage(data);
	/*	$("ul#list").html("");
		$.each(data,function(index,entry)
		{
			
			//$("ul#list3").append('<li>'+entry.item+'</li>');
			
		});
	}*/