import React, { useEffect } from "react";
import io from "socket.io-client"

const Dashboard = () => {
  const { REACT_APP_CENTRAL_SERVER } = process.env;
  const socket = io(REACT_APP_CENTRAL_SERVER);


  useEffect(() => {
    socket.on('connect', (socket) => {
      socket.data = "alice";
      console.log('[SOCKET] Socket is conected.');
    });
  }, []);

  return (
    <div>
      <h1>Dashboard</h1>
      <p>A socket io client</p>
    </div>
  );
}

export default Dashboard;
