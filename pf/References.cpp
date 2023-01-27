
//This is to see which object is in front of it and then react accordingly.

// if (map_.getObject(posX_, posY_ + 1) == '^')  
// {
//     hitObject = false;
//     newPosX_ = posX_;
//     newPosY_ = posY_ + 1;
//     inp = "up";
//     do
//     {
//         AlienMove(map_, inp, x, y);
//         AlienPlacement(map_);
//         pf::ClearScreen();
//         map_.display();
//         if (hitBarrier == true)
//         {
//             std::cout << "Alien hit the barrier!" << std::endl;
//             pf::Pause();
//         }
//         if (hitObject == true)
//         {
//             std::cout << "Alien hit an object!" << std::endl;
//             pf::Pause();
//         }
//     } while (hitBarrier == false && hitObject == false);
// }