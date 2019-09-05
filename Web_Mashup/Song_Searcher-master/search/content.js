var thisSong="";
var thisArtist="";
var videoSearch="";

function artistString(){
		var query = window.location.search;
		// Skip the leading ?, which should always be there, 
		// but be careful anyway
		if (query.substring(0, 1) == '?') {
			query = query.substring(1);
		}
		
		var x = document.getElementById("artist");
		x.textContent = (unescape(query)).toUpperCase();
		thisArtist=(unescape(query));
		
		getLyrics(unescape(query));
		//call last.fm api function call goes here
		getInfoArtist();
		//call youtube api function call goes here
}

function getLyrics(artistName){
	var artistSearch = artistName;
	document.getElementById("lyrics").textContent = "";
	  $.ajax({
		type: "GET",
		data: {
			apikey:"d41d9c85397808d9a48aeb95898f58ef",
			q_artist: artistSearch,
			format:"jsonp",
			callback:"jsonp_callback"
		},
		url: "http://api.musixmatch.com/ws/1.1/track.search",
		dataType: "jsonp",
		jsonpCallback: 'jsonp_callback',
		contentType: 'application/json',
		success: function(data) {
			var rand = data.message.body.track_list[Math.floor(Math.random() * data.message.body.track_list.length)];
			var thisTrack = (rand.track.track_id)
			var thisPic = rand.track.album_coverart_350x350;
			thisSong = rand.track.track_name;

			var songName = document.getElementById("songName");
			songName.textContent = thisSong;
			var p = document.createElement("p");
        	p.textContent = thisTrack;
        	p.id = thisTrack;

			document.getElementById("lyrics").appendChild(p).style.opacity = 0;
			
			getLyricsNow();

		},
		error: function(jqXHR, textStatus, errorThrown) {
			console.log(jqXHR);
			console.log(textStatus);
			console.log(errorThrown);
		}    
	 });
 };
 
function getLyricsNow(){
    var trackId = document.getElementById("lyrics").textContent;
    console.log(trackId)
  $.ajax({
    type: "GET",
    data: {
        apikey:"d41d9c85397808d9a48aeb95898f58ef",
        track_id: trackId,
        format:"jsonp",
        callback:"jsonp_callback"
    },
    url: "http://api.musixmatch.com/ws/1.1/track.lyrics.get",
    dataType: "jsonp",
    jsonpCallback: 'jsonp_callback',
    contentType: 'application/json',
    success: function(data) {
       console.log(data); console.log(data.message.body.lyrics.lyrics_body); 
      var lyricsBody = data.message.body.lyrics.lyrics_body.split(/\s+/).slice(0,100).join(" ")+ "...";
	  var lyricsBodyParsed=lyricsBody.split("...");
	  
       	var j = document.getElementById("lyrics2");
        j.textContent = lyricsBodyParsed[0] + "...";
        document.getElementById("lyrics").appendChild(j)
    },
    error: function(jqXHR, textStatus, errorThrown) {
        console.log(jqXHR);
        console.log(textStatus);
        console.log(errorThrown);
    }    
  });
};
 
 
 
 /*---------------------------------------------------------------------------------------------*/
 /*---------------------------------------------------------------------------------------------*/
 /*---------------------------------------------------------------------------------------------*/
 
function tplawesome(e,t){res=e;for(var n=0;n<t.length;n++){res=res.replace(/\{\{(.*?)\}\}/g,function(e,r){return t[n][r]})}return res}

function loadVideo(videoSearch){
		console.log(videoSearch);
	   // prepare the request
	   var request = gapi.client.youtube.search.list({
			part: "snippet",
			type: "video",
			q: encodeURIComponent(videoSearch).replace(/%20/g, "+"),
			maxResults: 1,
			publishedAfter: "2010-01-01T00:00:00Z"
	   }); 
	   // execute the request
	   request.execute(function(response) {
		   console.log(request);
		   console.log(response);
		  var results = response.result;
		  $("#results").html("");
		  $.each(results.items, function(index, item) {
			$.get("item.html", function(data) {
				$("#results").append(tplawesome(data, [{"title":item.snippet.title, "videoid":item.id.videoId}]));
			});
		  });
		  resetVideoHeight();
	   });
		
		$(window).on("resize", resetVideoHeight);
};

function resetVideoHeight() {
    $(".video").css("height", $("#results").width() * 9/16);
}

function init() {
    gapi.client.setApiKey("AIzaSyBpquJDOkrOahOhVbkGW6zF3m_4DbFG0NU");
    gapi.client.load("youtube", "v3", function() {
        // yt api is ready
		console.log("gapi initialized");
    });
}
 
 
 
 
 
 
    function getRelatedArtists(){
	 $(document).ready(function() {  
		//getting bio to put on information page
		$.getJSON("http://ws.audioscrobbler.com/2.0/?method=artist.getsimilar&artist="+ thisArtist +
		"&api_key=edb4edf05fcb1a68b1f808a7f138e1c4&limit=4&format=json&callback=?", 
		function(json)  {  
			//getting json and setting biographical information
			for(i=0; i<=3;++i)
			{

				var relatedArtistImage=document.getElementById("relatedArtistPicture"+i);
				relatedArtistImage.src=json.similarartists.artist[i].image[2]['#text'];
				console.log(json.similarartists.artist[i].image[1]['#text']);
				document.getElementById("relatedArtistName"+i).innerHTML = json.similarartists.artist[i].name;
				//console.log(json.topalbums.album[i].name);
				
			}
				 
		});
	});
		videoSearch = thisSong + thisArtist;
		$(loadVideo(videoSearch));
 };
  
  
  
  
  function getTopAlbums(){
	 $(document).ready(function() {  
		//getting bio to put on information page
		$.getJSON("http://ws.audioscrobbler.com/2.0/?method=artist.gettopalbums&artist="+ thisArtist +
		"&api_key=edb4edf05fcb1a68b1f808a7f138e1c4&limit=10&format=json&callback=?", 
		function(json)  {  
			//getting json and setting biographical information
			for(i=0; i<=2;++i)
			{
				if(json.topalbums.album[i].name=="(null)")
				{
					continue;
				}
				var artistImage=document.getElementById("albumArt"+i);
				artistImage.src=json.topalbums.album[i].image[2]['#text'];
				document.getElementById("albumName"+i).innerHTML = json.topalbums.album[i].name;
				console.log(json.topalbums.album[i].name);
				
			}
				 
		});
	});  
 };
 
 
 
 
 
 
 function getInfoArtist(){
	 $(document).ready(function() {  
		//getting bio to put on information page
		$.getJSON("http://ws.audioscrobbler.com/2.0/?method=artist.getinfo&artist="+ thisArtist +
		"&api_key=edb4edf05fcb1a68b1f808a7f138e1c4&limit=10&format=json&callback=?", 
		function(json)  {  
			
			//getting json and setting biographical information
			console.log(json.artist.name);
			var artistSummary= json.artist.bio.summary;
			var artistSummaryParsed=artistSummary.split(" <a");
			var informationText= document.getElementById("Information");
			informationText.textContent=(artistSummaryParsed[0]);
			

			//adding artist image
			var artistImage=document.getElementById("myImg");
			artistImage.src=json.artist.image[4]['#text'];
			
			//adding top album pictures and names
			getTopAlbums();
			getRelatedArtists();
			
				 
		});
	});  
 };
 
 
 
 
 