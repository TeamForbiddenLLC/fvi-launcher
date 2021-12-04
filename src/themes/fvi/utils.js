// gameOS theme
// Copyright (C) 2018-2020 Seth Powell 
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// This file contains some helper scripts for formatting data


// For multiplayer games, show the player count as '1-N'
function formatPlayers(playerCount) {
    if (playerCount === 1)
        return playerCount

    return "1-" + playerCount;
}


// Show dates in Y-M-D format
function formatDate(date) {
    return Qt.formatDate(date, "yyyy-MM-dd");
}


// Show last played time as text. Based on the code of the default Pegasus theme.
// Note to self: I should probably move this into the API.
function formatLastPlayed(lastPlayed) {
    if (isNaN(lastPlayed))
        return "never";

    var now = new Date();

    var elapsedHours = (now.getTime() - lastPlayed.getTime()) / 1000 / 60 / 60;
    if (elapsedHours < 24 && now.getDate() === lastPlayed.getDate())
        return "today";

    var elapsedDays = Math.round(elapsedHours / 24);
    if (elapsedDays <= 1)
        return "yesterday";

    return elapsedDays + " days ago"
}


// Display the play time (provided in seconds) with text.
// Based on the code of the default Pegasus theme.
// Note to self: I should probably move this into the API.
function formatPlayTime(playTime) {
    var minutes = Math.ceil(playTime / 60)
    if (minutes <= 90)
        return Math.round(minutes) + " minutes";

    return parseFloat((minutes / 60).toFixed(1)) + " hours"
}

// Process the platform name to make it friendly for the logo
// Unfortunately necessary for LaunchBox
function processPlatformName(platform) {
  switch (platform) {
    default:
      return platform;
  }
}

function processButtonArt(button) {
  var buttonModel;
  switch (button) {
    case "accept":
      buttonModel = api.keys.accept;
      break;
    case "cancel":
      buttonModel = api.keys.cancel;
      break;
    case "filters":
      buttonModel = api.keys.filters;
      break;
    case "details":
      buttonModel = api.keys.details;
      break;
    case "nextPage":
      buttonModel = api.keys.nextPage;
      break;
    case "prevPage":
      buttonModel = api.keys.prevPage;
      break;
    case "pageUp":
      buttonModel = api.keys.pageUp;
      break;
      case "pageDown":
        buttonModel = api.keys.pageDown;
        break;
    default:
      buttonModel = api.keys.accept;
  }

  var i;
  for (i = 0; buttonModel.length; i++) {
    if (buttonModel[i].name().includes("Gamepad")) {
      var buttonValue = buttonModel[i].key.toString(16)
      return buttonValue.substring(buttonValue.length-1, buttonValue.length);
    }
  }
}

function steamAppID (gameData) {
  var str = gameData.assets.boxFront.split("header");
  return str[0];
}

function steamBoxArt(gameData) {
  return steamAppID(gameData) + '/library_600x900_2x.jpg';
}

function steamLogo(gameData) {
  return steamAppID(gameData) + "/logo.png"
}

function steamHero(gameData) {
  return steamAppID(gameData) + "/library_hero.jpg"
}

// Just use boxFront?
function steamHeader(gameData) {
  return steamAppID(gameData) + "/header.jpg"
}

function boxArt(data) {
  if (data != null) {
    if (data.assets.boxFront.includes("/header.jpg")) 
      return steamBoxArt(data);
    else {
      if (data.assets.boxFront != "")
        return data.assets.boxFront;
      else if (data.assets.poster != "")
        return data.assets.poster;
      else if (data.assets.banner != "")
        return data.assets.banner;
      else if (data.assets.tile != "")
        return data.assets.tile;
      else if (data.assets.cartridge != "")
        return data.assets.cartridge;
      else if (data.assets.logo != "")
        return data.assets.logo;
    }
  }
  return "";
}

function logo(data) {
  if (data != null) {
    if (data.assets.boxFront.includes("/header.jpg")) 
      return steamLogo(data);
    else {
      if (data.assets.logo != "")
        return data.assets.logo;
    }
  }
  return "";
}

function fanArt(data) {
  if (data != null) {
    if (data.assets.boxFront.includes("/header.jpg")) 
      return steamHero(data);
    else {
      if (data.assets.background != "")
        return data.assets.background;
      else if (data.assets.screenshots[0])
        return data.assets.screenshots[0];
    }
  }
  return "";
}

// Reorder collection and remove items

function reorderCollection(model) {
  for(var i=0; i<model.count; i++) {
    	
	   if (model.get(i).name == "ITEMS") {
      model.remove(i,0);
      return model;
    }
  
  }
  return model;
}

// Shuffle function
function shuffle(model){
  var currentIndex = model.count, temporaryValue, randomIndex;

  // While there remain elements to shuffle...
  while (0 !== currentIndex) {
      // Pick a remaining element...
      randomIndex = Math.floor(Math.random() * currentIndex)
      currentIndex -= 1
      // And swap it with the current element.
      // the dictionaries maintain their reference so a copy should be made
      // https://stackoverflow.com/a/36645492/6622587
      temporaryValue = JSON.parse(JSON.stringify(model.get(currentIndex)))
      model.set(currentIndex, model.get(randomIndex))
      model.set(randomIndex, temporaryValue);
  }
  
  return model;
}

function uniqueGameValues(fieldName) {
  const set = new Set();
  api.allGames.toVarArray().forEach(game => {
      game[fieldName].forEach(v => set.add(v));
  });
  return [...set.values()].sort();
}

function uniqueValuesArray(fieldName) {
  let arr = [];
  var allGames = api.allGames.toVarArray();
  for(var i=0;i<allGames.length;i++) {
    arr.push(allGames[i][fieldName]);
  }
  return arr;
}

function shuffleArray(array) {
  var currentIndex = array.length, temporaryValue, randomIndex;

  // While there remain elements to shuffle...
  while (0 !== currentIndex) {

      // Pick a remaining element...
      randomIndex = Math.floor(Math.random() * currentIndex);
      currentIndex -= 1;

      // And swap it with the current element.
      temporaryValue = array[currentIndex];
      array[currentIndex] = array[randomIndex];
      array[randomIndex] = temporaryValue;
  }

  return array;
}

function returnRandom(array) {
  return array[Math.floor(Math.random() * array.length)];
}