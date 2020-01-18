/*--------------------------------------------------------------------------
* Project: Reat Over QML / Qt Project
* Author Fabrice Lainard Created : 18/01/2020
*
* Copyright (c) Fabtice Lainard Programming. All rights reserved.
* Licensed under the MIT License.
--------------------------------------------------------------------------*/

import React from 'react';
import { Button, Card, Elevation, FormGroup, InputGroup } from "@blueprintjs/core";
import Qt from './qwebchannel.js';
import './App.css';


class App extends React.Component {

  constructor(props) {
    super(props);
    this.state = {
      list: [],
    }
  }

  componentDidMount() {
    let self = this;
    var socket = new WebSocket("ws://localhost:89");
   
    socket.onopen = function () {
      self.qWebChannel = new Qt.QWebChannel(socket, function (channel) {
        self.backend = channel.objects.backend;

        // init list at startup
        self.setState({
          list: self.backend.list
        });
          
        // Connect to a refresh signal:
        self.backend.listChanged.connect(function () {
          self.setState({
            list: self.backend.list
          });
           
        });

      });
    };
  }

  handleInputChange = (event) => {
    const target = event.target;
    const value = target.value;
    this.lastValue = value;
  }


  onAdd = (e) => {
    if (!this.lastValue) return;
    this.backend.addListElement(this.lastValue);
  }



  render() {
    const rightElement = (<Button iconOnly={true} icon="refresh" onClick={(e) => this.onAdd(e)}>Add element</Button>)

    const SimpleList = () => (
      <ul>
        {this.state.list.map(item => {
          return <li key={item}>{item}</li>;
        })}
      </ul>
    );
    return (
      <div class="main">
        <nav class="bp3-navbar bp3-dark">
          <div  >
            <div class="bp3-navbar-group bp3-align-left">
              <div class="bp3-navbar-heading">Qml Vs React - Fabrice Lainard Programming</div>
            </div>
            <div class="bp3-navbar-group bp3-align-right">
              <button class="bp3-button bp3-minimal bp3-icon-home">Home</button>
              <button class="bp3-button bp3-minimal bp3-icon-document">Files</button>
              <span class="bp3-navbar-divider"></span>
              <button class="bp3-button bp3-minimal bp3-icon-user"></button>
              <button class="bp3-button bp3-minimal bp3-icon-notifications"></button>
              <button class="bp3-button bp3-minimal bp3-icon-cog"></button>
            </div>
          </div>
        </nav>
        <div className="appContainer">
          <div className="formContainer">
            <Card className="bp3-dark" interactive={true} elevation={Elevation.TWO}>
              <h3><a href="#">C++/Qt integrated Qml Vs React - Fabrice Lainard Programming</a></h3>
              <FormGroup
                helperText="Type text used to add in list"
                label="Input text"
                labelFor="text-input"
                labelInfo="(required)"
              > <InputGroup className="textInput" id="text-input" placeholder="User Name" rightElement={rightElement} onBlur={this.handleInputChange} />
              </FormGroup>
              <SimpleList></SimpleList>
            </Card>
          </div>
        </div>


      </div>
    );
  }
}


export default App;
